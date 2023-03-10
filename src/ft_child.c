/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:30:06 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/20 16:28:10 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exec_cmd(t_data *data, int i)
{
	if (ft_strchr (data->cmds[i].name, '/') != NULL)
	{
		ft_assert_not_dir (data, data->cmds[i].pathname, true);
		ft_assert_valid_permissions (data, data->cmds[i].pathname, X_OK,
			true);
	}
	ft_shift (data, &data->cmds[i].args, data->cmds[i].pathname);
	execve(data->cmds[i].pathname,
		data->cmds[i].args, data->envp);
	ft_throw(data, ERR_FAIL, "execve", true);
}

static void	ft_pipe(t_data *data, int j, t_stream s)
{
	t_fd	fd;
	int		iofd;

	if (data->pipes == NULL || data->cmdsc_pps <= 1
		|| (s == STREAM_INPUT && j < 1)
		|| (s == STREAM_OUTPUT && j == data->cmdsc_pps - 1))
		return ;
	ft_assert_not_null (data, data);
	if (s == STREAM_INPUT)
		fd = data->pipes[(j - 1) * 2];
	else
		fd = data->pipes[(j * 2) + 1];
	iofd = STDIN_FILENO;
	if (s == STREAM_OUTPUT)
		iofd = STDOUT_FILENO;
	if (dup2 (fd, iofd) == -1)
		ft_throw (data, ERR_FAIL, "dup2", true);
}

static void	ft_prepare_cmd_exec(t_data *data, pid_t *pid,
	int *infd, int *outfd)
{
	*infd = STDIN_FILENO;
	*outfd = STDOUT_FILENO;
	*pid = fork();
	if (*pid == -1)
		ft_throw(data, ERR_FAIL, "fork", true);
}

static void	ft_exec_cmd_or_builtin1(t_data *data, int i, int j)
{
	pid_t	pid;
	t_fd	infd;
	t_fd	outfd;

	ft_prepare_cmd_exec (data, &pid, &infd, &outfd);
	if (pid == 0)
	{
		ft_signals (SIG_CHILD);
		ft_pipe(data, j, STREAM_INPUT);
		ft_pipe(data, j, STREAM_OUTPUT);
		ft_redirect(data, i);
		ft_close(data, infd, outfd);
		if (ft_isbuiltin (data->cmds[i].name) == 1)
			ft_exec_builtin (data, i, data->cmds[i].name);
		else if (data->cmds[i].pathname != NULL)
			ft_exec_cmd (data, i);
		ft_throw(data, ERR_CMD_NOT_FOUND, data->cmds[i].name, true);
	}
}

void	ft_child(t_data *data, int i, int j)
{
	ft_assert_not_null (data, data);
	ft_assert_not_null (data, data->cmds);
	ft_expand_str (data, &data->cmds[i].name, NULL, -1);
	ft_explode_name (data, i);
	ft_expand_tab (data, &data->cmds[i].args);
	if (ft_isbuiltin (data->cmds[i].name) == 2)
		ft_exec_builtin (data, i, data->cmds[i].name);
	else
	{
		if (ft_strchr (data->cmds[i].name, '/') != NULL)
			data->cmds[i].pathname = ft_strdup (data->cmds[i].name);
		else
			data->cmds[i].pathname = ft_pathname
				(data, data->cmds[i].name);
		ft_exec_cmd_or_builtin1 (data, i, j);
	}
}
