/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:23:25 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/11 11:13:39 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_pipe(t_data *data, int i, t_fd *iofd, t_stream s)
{
	t_fd	fd;

	if (data->pipes == NULL || data->cmdsc <= 1
		|| (s == STREAM_INPUT && i < 1)
		|| (s == STREAM_OUTPUT && i == data->cmdsc -1))
		return ;
	ft_assert_not_null (data, data);
	ft_assert_not_null (data, iofd);
	if (s == STREAM_INPUT)
		fd = data->pipes[(i - 1) * 2];
	else
		fd = data->pipes[(i * 2) + 1];
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
	while (++i < (data->cmdsc - 1) * 2)
		if (data->pipes[i] != infd && data->pipes[i] != outfd)
			close (data->pipes[i]);
}

static void	ft_child(t_data *data, int i)
{
	t_fd	infd;
	t_fd	outfd;
	
	ft_assert_not_null (data, data);
	ft_assert_not_null (data, data->cmds);
	infd = STDIN_FILENO;
	infd = STDOUT_FILENO;
	data->cmds[i].pid = fork ();
	if (data->cmds[i].pid == -1)
		ft_throw (data, ERR_FAIL, "fork", true);
	if (data->cmds[i].pid == 0)
	{
		ft_pipe (data, i, &infd, STREAM_INPUT);
		ft_redirect (data, i, &infd, &outfd);
		ft_pipe (data, i, &outfd, STREAM_OUTPUT);
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

// static void	ft_prepare(t_data *data)
// {
// 	int	i;
	
// 	i = -1;
// 	if (data->cmdsc > 1)
// 	{
// 		data->pipes = (t_fd *) malloc ((data->cmdsc - 1) * 2 * sizeof (t_fd));
// 		ft_assert_not_null (data, data->pipes);
// 		i = -1;
// 		while (++i < data->cmdsc - 1)
// 			if (pipe (data->pipes + (2 * i)) == -1)
// 				ft_throw (data, ERR_FAIL, "pipe", true);
// 	}
// 	data->pids = (pid_t *) malloc (data->cmdsc * sizeof (pid_t));
// }

// static bool	ft_loop (t_data *data, int lvl, int *i)
// {
// 	int	c;
// 	int	wstatus;
	
// 	ft_assert_not_null (data, data);
// 	while (data->cmds[*i].lvl = 0 || data->cmds[*i].lvl == lvl)
// 	{
// 		if (data->cmds[*i].lvl != lvl)
// 			ft_loop (data, lvl + 1, *i);
// 		ft_child (data, *i, STDIN_FILENO, STDOUT_FILENO);
// 		wait (&wstatus);
// 		if (*i == data->cmdsc - 1 
// 			|| (wstatus != 0 && data->cmds[*i + 1].inst == I_AND))
// 			return (false);
// 	}
// 	return (true);
// }

static bool ft_loop(t_data *data, int lvl, int *i)
{
	// int	pipesc;
	int status;

	ft_assert_not_null (data, data);
	status = 0;
	while (data->cmds[*i].lvl >= lvl && *i < data->cmdsc)
	{
		if (data->cmds[*i].lvl > 0)
			ft_loop (data, data->cmds[*i].lvl, i);
		else if (data->cmds[*i].inst == I_START
			|| (data->cmds[*i].inst == I_OR && status != 0)
			|| (data->cmds[*i].inst == I_AND && status == 0))
		{
			ft_child (data, *i);
			wait (&status);
			ft_putnbr_fd (status, 2);
		}
		(*i)++;
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
