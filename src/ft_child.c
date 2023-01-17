/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:30:06 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/17 17:27:25 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_prepare_cmd_exec(t_data *data, pid_t *pid,
	int *infd, int *outfd)
{
	*infd = STDIN_FILENO;
	*outfd = STDOUT_FILENO;
	*pid = fork();
	if (*pid == -1)
		ft_throw(data, ERR_FAIL, "fork", true);
}

static void	ft_exec_cmd(t_data *data, int i)
{
	if (ft_strchr (data->cmds[i].name, '/') != NULL)
	{
		ft_assert_not_dir (data, data->cmds[i].pathname, true);
		ft_assert_valid_permissions (data, data->cmds[i].pathname, X_OK);
	}
	ft_shift (data, &data->cmds[i].args, data->cmds[i].pathname);
	execve(data->cmds[i].pathname,
		data->cmds[i].args, data->envp);
	ft_putendl_fd (data->cmds[i].pathname, 2);
	ft_throw(data, ERR_FAIL, "execve", true);
}

static void	ft_exec_cmd_or_builtin1(t_data *data, int i, int j)
{
	pid_t	pid;
	t_fd	infd;
	t_fd	outfd;

	ft_prepare_cmd_exec (data, &pid, &infd, &outfd);
	if (pid == 0)
	{
		ft_pipe(data, j, &infd, STREAM_INPUT);
		ft_redirect(data, i, &infd, &outfd);
		ft_pipe(data, j, &outfd, STREAM_OUTPUT);
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
	ft_expand_str (data, &data->cmds[i].name);
	ft_expand_tab (data, data->cmds[i].args);
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
