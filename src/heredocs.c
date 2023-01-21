/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 17:41:10 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/21 13:22:37 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_isheredoc_lim(char *heredoc_lim, char *buff)
{
	if (heredoc_lim != NULL && buff != NULL)
		if (ft_strncmp(heredoc_lim, buff, ft_strlen(heredoc_lim) + 1) == 0)
			return (true);
	return (false);
}

static void	ft_read(t_data *data, int fd, char *heredoc_lim)
{
	char	*buff;
	char	*line;

	ft_assert_not_null (data, data);
	while (1)
	{
		buff = readline("> ");
		if (buff != NULL && !ft_isheredoc_lim(heredoc_lim, buff))
		{
			line = ft_strjoin(buff, "\n");
			if (line != NULL)
				write(fd, line, ft_strlen(line));
			free(line);
			free(buff);
		}
		else
		{
			free(buff);
			break ;
		}
	}
}

static t_fd	ft_heredoc(t_data *data, char *heredoc_lim)
{
	t_fd	fd;

	if (heredoc_lim == NULL)
		return (-1);
	fd = open ("temp.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		ft_throw (data, ERR_FAIL, "file write", true);
	ft_read(data, fd, heredoc_lim);
	close (fd);
	fd = open ("temp.tmp", O_RDONLY, 0644);
	unlink ("temp.tmp");
	return (fd);
}

static void	ft_handlecmd_heredocs(t_data *data, int i)
{
	int		j;
	char	*fd;
	int		infd_cp;

	ft_assert_not_null (data, data);
	ft_assert_not_null (data, data->cmds[i].redirs);
	ft_assert_not_null (data, data->cmds[i].args_redir);
	j = -1;
	while (++j < data->cmds[i].redirsc)
	{
		if (data->cmds[i].redirs[j] == REDIR_HEREDOC)
		{
			infd_cp = dup (STDIN_FILENO);
			ft_signals (SIG_HEREDOC);
			ft_str_remove_quotes(data, data->cmds[i].args_redir + j);
			fd = ft_itoa (ft_heredoc (data,
						data->cmds[i].args_redir[j]));
			ft_assert_not_null (data, fd);
			dup2 (infd_cp, STDIN_FILENO);
			close (infd_cp);
			free (data->cmds[i].args_redir[j]);
			data->cmds[i].args_redir[j] = fd;
			ft_signals (SIG_PARENT);
		}
	}
}

void	ft_heredocs(t_data *data)
{
	int		i;

	ft_assert_not_null (data, data);
	ft_assert_not_null (data, data->cmds);
	i = -1;
	while (++i < data->cmdsc)
		if (data->cmds[i].redirsc > 0)
			ft_handlecmd_heredocs (data, i);
}
