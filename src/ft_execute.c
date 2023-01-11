/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:23:25 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/11 17:00:17 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_pipe(t_data *data, int j, t_fd *iofd, t_stream s)
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

static void	ft_close(t_data *data, int infd, int outfd)
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

static void	ft_child(t_data *data, int i, int j)
{
	pid_t	pid;
	t_fd	infd;
	t_fd	outfd;
	
	ft_assert_not_null (data, data);
	ft_assert_not_null (data, data->cmds);
	infd = STDIN_FILENO;
	outfd = STDOUT_FILENO;
	pid = fork ();
	if (pid == -1)
		ft_throw (data, ERR_FAIL, "fork", true);
	if (pid == 0)
	{
		ft_pipe (data, j, &infd, STREAM_INPUT);
		ft_redirect (data, i, &infd, &outfd);
		ft_pipe (data, j, &outfd, STREAM_OUTPUT);
		ft_close (data, infd, outfd);
		if (ft_isbuiltin (data->cmds[i].name))
			ft_builtin (data, i, data->cmds[i].name);
		else if (data->cmds[i].pathname != NULL)
		{
			execve (data->cmds[i].pathname,
				data->cmds[i].args, data->envp);
			ft_throw (data, ERR_FAIL, "execve", true);
		}
		ft_throw (data, ERR_CMD_NOT_FOUND, data->cmds[i].name, true);
	}
}

static int	ft_peek_cmdsc(t_data *data, int i)
{
	int cmdsc;

	cmdsc = 1;
	while (++i < data->cmdsc && data->cmds[i].inst == I_PIPE)
		cmdsc++;
	return (cmdsc);
}

static bool ft_loop(t_data *data, int lvl, int *i)
{
	int status;
	int	j;

	ft_assert_not_null (data, data);
	status = 0;
	while (data->cmds[*i].lvl >= lvl && *i < data->cmdsc)
	{
		if (data->cmds[*i].lvl > lvl)
		{
			if (data->cmds[*i].inst == I_START
				|| (data->cmds[*i].inst == I_OR && status != 0)
				|| (data->cmds[*i].inst == I_AND && status == 0))
				ft_loop (data, data->cmds[*i].lvl, i);
			else
			{
				while (data->cmds[*i].lvl > lvl && *i < data->cmdsc)
					(*i)++;
			}
		}
		else
		{
			if (data->cmds[*i].inst == I_START
				|| (data->cmds[*i].inst == I_OR && status != 0)
				|| (data->cmds[*i].inst == I_AND && status == 0))
			{
				data->cmdsc_pps = ft_peek_cmdsc (data, *i);
				data->pipes = ft_initpipes (data, data->cmdsc_pps);
				j = -1;
				while (++j < data->cmdsc_pps)
				{
					ft_child (data, *i, j);
					(*i)++;
				}
				if (data->pipes != NULL)
				{
					j = -1;
					while (++j < (data->cmdsc_pps - 1) * 2)
						close (data->pipes[j]);
				}
				j = -1;
				while (++j < data->cmdsc_pps)
					wait (&status);
				if (data->pipes != NULL)
				{
					free (data->pipes);
					data->pipes = NULL;
				}
			}
			else
				(*i)++;
		}
	}
	return (true);
}

void	ft_execute(t_data *data)
{
	int	i;

	ft_assert_not_null (data, data);
	if (data->cmds == NULL)
		ft_throw (data, ERR_NULL_PTR, "ft_execute data->cmds", true);
	i = 0;
	ft_loop (data, 0, &i);
}
