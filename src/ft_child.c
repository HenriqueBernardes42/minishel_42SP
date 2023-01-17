/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:30:06 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/17 14:45:52 by rburgsta         ###   ########.fr       */
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

static void	ft_exec_cmd(t_data *data, int i, int j)
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
		{
			ft_expand_tab(data, data->cmds[i].args);
			execve(data->cmds[i].pathname,
				data->cmds[i].args, data->envp);
			ft_throw(data, ERR_FAIL, "execve", true);
		}
		ft_throw(data, ERR_CMD_NOT_FOUND, data->cmds[i].name, true);
	}
}

void	ft_child(t_data *data, int i, int j)
{
	ft_assert_not_null (data, data);
	ft_assert_not_null (data, data->cmds);
	if (ft_isbuiltin (data->cmds[i].name) == 2)
		ft_exec_builtin (data, i, data->cmds[i].name);
	else
		ft_exec_cmd (data, i, j);
}
