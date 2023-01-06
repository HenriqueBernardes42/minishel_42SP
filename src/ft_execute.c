/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:23:25 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/06 23:55:25 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_redirect_io(t_data *data, int i, t_fd *infd, t_fd *outfd)
{
	t_fd	tempfd;
	int	j;

	j = data->cmds[i].redirsc;
	while (--j >= 0)
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
			{
				tempfd = open (data->cmds[i].args_redir[j], O_WRONLY | O_CREAT
					| O_TRUNC, 0644);
			}
			else
			{
				tempfd = open (data->cmds[j].args_redir[j], O_WRONLY | O_CREAT
					| O_APPEND, 0644);
			}
		}
		ft_assert_not_equal (data, tempfd, -1, ERR_ENOENT);
		if (data->cmds[i].redirs[j] == REDIR_INFILE
			|| data->cmds[i].redirs[j] == REDIR_HEREDOC)
		{
			ft_assert_not_equal (data, dup2 (tempfd, *infd), -1, ERR_DUP2_FAIL);
			*infd = tempfd;
		}
		else
		{
			ft_assert_not_equal (data, dup2 (tempfd, *outfd), -1, ERR_DUP2_FAIL);
			*outfd = tempfd;
			ft_putnbr_fd (*outfd, 2);
		}
	}
}

static void	ft_pipein(t_data *data, int i, t_fd *infd)
{
	t_fd	fd;
	
	ft_assert_not_null (data, data);
	if (i < 1)
		return ;
	fd = data->pipes[(i - 1) * 2];
	// printf ("pipein: %d->%d instead of %d \n", (i - 1) * 2, data->pipes[(i - 1) * 2], *infd);
	ft_assert_not_equal (data, dup2 (fd, *infd), -1, ERR_DUP2_FAIL);
	*infd = fd;
}

static void	ft_pipeout(t_data *data, int i, t_fd *outfd)
{
	t_fd	fd;
	
	ft_assert_not_null (data, data);
	if (i == data->cmdsc - 1)
		return ;
	fd = data->pipes[(i * 2) + 1];
	ft_assert_not_equal (data, dup2 (fd, *outfd), -1, ERR_DUP2_FAIL);
	*outfd = fd;
}

static void	ft_close(t_data *data, int infd, int outfd)
{
	int		i;
	
	i = -1;
	while (++i < (data->cmdsc - 1) * 2)
		if (data->pipes[i] != infd && data->pipes[i] != outfd)
			close (data->pipes[i]);
}

static void	ft_child(t_data *data, int i)
{
	t_fd	infd;
	t_fd	outfd;
	t_pid	pid;
	
	ft_assert_not_null (data, data);
	ft_assert_not_null (data, data->cmds);
	infd = STDIN_FILENO;
	outfd = STDOUT_FILENO;
	pid = fork ();
	if (pid == -1)
		ft_throw (data, ERR_FORK_FAIL, "ft_child", true);
	if (pid == 0)
	{
		if (data->cmdsc > 1 && i > 0)
			ft_pipein (data, i, &infd);
		if (data->cmds[i].redirs != NULL)
			ft_redirect_io (data, i, &infd, &outfd);
		if (data->cmdsc > 1 && i != data->cmdsc - 1)
			ft_pipeout (data, i, &outfd);
		ft_putnbr_fd (outfd, 2);
		ft_close (data, infd, outfd);
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
	while (++i < (data->cmdsc - 1) * 2)
		close (data->pipes[i]);
	i = -1;
	while (++i < data->cmdsc)
		wait (NULL);
}
