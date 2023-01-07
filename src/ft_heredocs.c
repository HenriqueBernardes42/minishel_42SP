/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredocs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 17:41:10 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/07 20:39:50 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_isheredoc_lim(char *heredoc_lim, char *buff)
{
	char	*heredoc_limendl;

	if (heredoc_lim != NULL && buff != NULL)
	{
		heredoc_limendl = ft_strjoin (heredoc_lim, "\n");
		if (heredoc_limendl != NULL)
		{
			if (ft_strncmp (heredoc_limendl, buff,
					ft_strlen (heredoc_limendl) + 1) == 0)
			{
				free (heredoc_limendl);
				return (true);
			}
			free (heredoc_limendl);
		}
	}
	return (false);
}

static void	ft_read(int fd, char *heredoc_lim)
{
	char	buff[BUFFER_SIZE];
	int		count;

	while (1)
	{
		ft_putstr_fd ("> ", STDERR_FILENO);
		count = read (STDIN_FILENO, buff, BUFFER_SIZE - 1);
		if (count <= 0)
			break ;
		else
		{
			buff[count] = '\0';
			if (!ft_isheredoc_lim (heredoc_lim, buff))
				write (fd, buff, count);
			else
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
	ft_read(fd, heredoc_lim);
	close (fd);
	fd = open ("temp.tmp", O_RDONLY, 0644);
	unlink ("temp.tmp");
	return (fd);
}

static void	ft_handlecmd_heredocs(t_data *data, int i)
{
	int		j;
	char	*fd;

	ft_assert_not_null (data, data);
	ft_assert_not_null (data, data->cmds[i].redirs);
	ft_assert_not_null (data, data->cmds[i].args_redir);
	j = -1;
	while (++j < data->cmds[i].redirsc)
	{
		if (data->cmds[i].redirs[j] == REDIR_HEREDOC)
		{
			fd = ft_itoa (ft_heredoc (data,
						data->cmds[i].args_redir[j]));
			ft_assert_not_null (data, fd);
			free (data->cmds[i].args_redir[j]);
			data->cmds[i].args_redir[j] = fd;
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
