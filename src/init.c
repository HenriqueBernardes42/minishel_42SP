/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 19:45:27 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/02 21:22:07 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_initcmd(t_data *data)
{
	t_cmd	*cmd;

	cmd = (t_cmd *) malloc (sizeof (t_cmd));
	ft_assert_not_null (data, cmd);
	cmd->name = NULL;
	cmd->pathname = NULL;
	cmd->args = NULL;
	cmd->argsc = 0;
	cmd->infiles = NULL;
	cmd->outfiles = NULL;
	return (cmd);
}

t_cmd	**ft_initcmds(t_data *data)
{
	t_cmd	**cmds;

	cmds = (t_cmd **) malloc (2 * sizeof (t_cmd *));
	cmds[0] = NULL;
	cmds[1] = NULL;
	return (cmds);
}

t_exec	**ft_initexecs(t_data *data)
{
	t_exec	**execs;

	execs = (t_exec **) malloc (2 * sizeof (t_exec *));
	execs[0] = NULL;
	execs[1] = NULL;
	return (execs);
}

t_exec	*ft_initexec(t_data *data)
{
	t_exec	*exec;

	exec = (t_exec *) malloc (sizeof (t_exec));
	ft_assert_not_null (data, exec);
	exec->cmds = NULL;
	exec->cmdsc = 0;
	exec->next = NULL;
	return (exec);
}

t_data 	*ft_initdata(void)
{
	t_data	*data;

	data = (t_data *) malloc (sizeof (t_data));
	ft_assert_not_null (data, data);
	data->envp = NULL;
	data->path = NULL;
	data->input = NULL;
	data->execs = NULL;
	data->execsc = -1;
	return (data);
}
