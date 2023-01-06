/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:23:25 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/06 20:55:17 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_redirect_io(t_data *data, int i)
{
	t_fd	infd;
	t_fd	outfd;
	t_fd	tempfd;
	int	j;

	infd = STDIN_FILENO;
	outfd = STDIN_FILENO;
	j = -1;
	while (++j < data->cmds[i].redirsc)
	{
		tempfd = -1;
		if (data->cmds[i].redirs[j] == REDIR_INFILE
			|| data->cmds[i].redirs[j] == REDIR_OUTFILE_TRC
			|| data->cmds[i].redirs[j] == REDIR_OUTFILE_APP)
			ft_assert_not_dir (data, data->cmds[i].args_redir[j]);
		if (data->cmds[i].redirs[j] == REDIR_INFILE)
		{
			ft_assert_valid_permissions (data, data->cmds[i].args_redir[j], R_OK);
			tempfd = open (data->cmds[j].args_redir[j], O_RDONLY);
		}
		else if (data->cmds[i].redirs[j] == REDIR_HEREDOC)
			tempfd = ft_heredoc (data, data->cmds[i].args_redir[j]);
		else if (data->cmds[i].redirs[j] == REDIR_OUTFILE_TRC ||
			data->cmds[i].redirs[j] == REDIR_OUTFILE_APP)
		{
			ft_assert_valid_permissions (data, data->cmds[i].args_redir[j], W_OK);
			if (data->cmds[i].redirs[j] == REDIR_OUTFILE_TRC)
				tempfd = open (data->cmds[j].args_redir[j], O_WRONLY | O_CREAT
					| O_TRUNC, 0644);
			else
				tempfd = open (data->cmds[j].args_redir[j], O_WRONLY | O_CREAT
					| O_APPEND, 0644);
		}
		ft_assert_not_equal (data, tempfd, -1, ERR_ENOENT);
		if (data->cmds[i].redirs[j] == REDIR_INFILE
			|| data->cmds[i].redirs[j] == REDIR_HEREDOC)
		{
			ft_assert_not_equal (data, dup2 (tempfd, infd), -1, ERR_DUP2_FAIL);
			infd = tempfd;
		}
		else
		{
			ft_assert_not_equal (data, dup2 (tempfd, outfd), -1, ERR_DUP2_FAIL);
			outfd = tempfd;
		}
	}
}

static void	ft_child(t_data *data, int i)
{
	t_pid	pid;
	
	ft_assert_not_null (data, data);
	ft_assert_not_null (data, data->cmds);
	
	pid = fork ();
	if (pid == -1)
		ft_throw (data, ERR_FORK_FAIL, "ft_child", true);
	if (pid == 0)
	{
		if (data->cmds[i].redirs != NULL)
			ft_redirect_io (data, i);
		if (data->cmds[i].pathname != NULL)
		{
			execve (data->cmds[i].pathname
				, data->cmds[i].args, data->envp);
			ft_throw (data, ERR_EXECVE_FAIL, NULL, true);
		}
		else
			ft_throw (data, ERR_CMD_NOT_FOUND, data->cmds[i].name, true);
	}
}

void	ft_execute(t_data *data)
{
	int	i;

	ft_assert_not_null (data, data);
	if (data->cmds == NULL)
		ft_throw (data, ERR_NULL_PTR, "ft_execute data->cmds", true);
	i = -1;
	if (data->cmdsc > 1)
	{
		data->pipes = (t_fd *) malloc ((data->cmdsc - 1) * 2 * sizeof (t_fd));
		ft_assert_not_null (data, data->pipes);
		i = -1;
		while (++i < data->cmdsc)
			ft_assert_not_equal (data, pipe (data->pipes + (2 * i))
				, -1, ERR_PIPE_FAIL);
	}
	i = -1;
	while (++i < data->cmdsc)
		ft_child (data, i);
	i = -1;
	while (++i < data->cmdsc)
		wait (NULL);
}
