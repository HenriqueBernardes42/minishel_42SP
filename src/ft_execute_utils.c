/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 10:23:40 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/12 10:56:40 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_anticipate_cmdsc(t_data *data, int i)
{
	int	cmdsc;

	cmdsc = 1;
	while (++i < data->cmdsc && data->cmds[i].inst == I_PIPE)
		cmdsc++;
	return (cmdsc);
}

void	ft_pipe(t_data *data, int j, t_fd *iofd, t_stream s)
{
	t_fd	fd;

	if (data->pipes == NULL || data->cmdsc_pps <= 1
		|| (s == STREAM_INPUT && j < 1)
		|| (s == STREAM_OUTPUT && j == data->cmdsc_pps -1))
		return ;
	ft_assert_not_null (data, data);
	ft_assert_not_null (data, iofd);
	if (s == STREAM_INPUT)
		fd = data->pipes[(j - 1) * 2];
	else
		fd = data->pipes[(j * 2) + 1];
	if (dup2 (fd, *iofd) == -1)
		ft_throw (data, ERR_FAIL, "dup2", true);
	*iofd = fd;
}

void	ft_close(t_data *data, int infd, int outfd)
{
	int		i;

	if (data->pipes == NULL)
		return ;
	ft_assert_not_null (data, data);
	i = -1;
	while (++i < (data->cmdsc_pps - 1) * 2)
		if (data->pipes[i] != infd && data->pipes[i] != outfd)
			close (data->pipes[i]);
}

static void	ft_prepare_child(t_data *data, pid_t *pid,
	t_fd *infd, t_fd *outfd)
{
	*infd = STDIN_FILENO;
	*outfd = STDOUT_FILENO;
	*pid = fork ();
	if (*pid == -1)
		ft_throw (data, ERR_FAIL, "fork", true);
}

void	ft_child(t_data *data, int i, int j)
{
	pid_t	pid;
	t_fd	infd;
	t_fd	outfd;

	ft_assert_not_null (data, data);
	ft_assert_not_null (data, data->cmds);
	ft_prepare_child (data, &pid, &infd, &outfd);
	if (pid == 0)
	{
		ft_pipe (data, j, &infd, STREAM_INPUT);
		ft_redirect (data, i, &infd, &outfd);
		ft_pipe (data, j, &outfd, STREAM_OUTPUT);
		ft_close (data, infd, outfd);
		if (ft_isbuiltin (data->cmds[i].name))
			ft_exec_builtin (data, i, data->cmds[i].name);
		else if (data->cmds[i].pathname != NULL)
		{
			execve (data->cmds[i].pathname,
				data->cmds[i].args, data->envp);
			ft_throw (data, ERR_FAIL, "execve", true);
		}
		ft_throw (data, ERR_CMD_NOT_FOUND, data->cmds[i].name, true);
	}
}
