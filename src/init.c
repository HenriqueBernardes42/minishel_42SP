/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 21:37:57 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/24 18:17:25 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_args2	*ft_initargs2(t_data *data, int i)
{
	t_args2	*args2;

	ft_assert_not_null (data, data->cmds);
	if (i >= data->cmdsc)
		ft_throw (data, ERR_INVALID_CMDSC, NULL, true);
	args2 = (t_args2 *) malloc (sizeof (t_args2));
	ft_assert_not_null (data, args2);
	args2->i = i;
	args2->j = data->cmds[i].redirsc;
	args2->iofd = -1;
	args2->infd = STDIN_FILENO;
	args2->outfd = STDOUT_FILENO;
	return (args2);
}

t_args	*ft_initargs(t_data *data, char *pathname)
{
	t_args	*args;
	int		i;

	args = (t_args *) malloc (sizeof (t_args));
	ft_assert_not_null (data, args);
	args->count = 0;
	args->path = NULL;
	if (pathname != NULL)
	{
		args->tab = ft_split (pathname, '/');
		i = -1;
		while (args->tab[++i] != NULL)
			args->count++;
	}
	else
		args->tab = NULL;
	args->err = ERR_EACCES;
	args->temp = NULL;
	return (args);
}

t_cmd	*ft_initcmds(t_data *data, int cmdsc)
{
	t_cmd	*cmds;
	int		i;

	if (cmdsc < 0)
		ft_throw (data, ERR_INVALID_CMDSC, NULL, true);
	cmds = (t_cmd *) malloc (cmdsc * sizeof (t_cmd));
	ft_assert_not_null (data, cmds);
	i = -1;
	while (++i < cmdsc)
	{
		cmds[i].name = NULL;
		cmds[i].pathname = NULL;
		cmds[i].args = NULL;
		cmds[i].argsc = 0;
		cmds[i].args_redir = NULL;
		cmds[i].redirs = NULL;
		cmds[i].redirsc = 0;
		cmds[i].lvl = -1;
		cmds[i].instr = I_UNDEF;
	}
	return (cmds);
}

static void	ft_initdata_envp(t_data *data, char **envp)
{
	int	i;

	ft_assert_not_null (data, data);
	data->envp = (char **) malloc ((ft_tablen (envp) + 1) * sizeof (char *));
	if (data->envp == NULL)
		ft_throw (data, ERR_FAIL, "malloc", true);
	i = ft_tablen (envp);
	data->envp[i] = NULL;
	while (--i >= 0)
		data->envp[i] = ft_strdup (envp[i]);
	ft_update_shlvl(data);
}

t_data	*ft_initdata(char **envp)
{
	t_data	*data;

	data = (t_data *) malloc (sizeof (t_data));
	ft_assert_not_null (data, data);
	if (envp != NULL)
		ft_initdata_envp (data, envp);
	data->line = NULL;
	data->tab = NULL;
	data->cmds = NULL;
	data->cmdsc = -1;
	data->pipes = NULL;
	data->cmdsc_pps = -1;
	data->status = 0;
	data->history = NULL;
	data->where_history = 0;
	if (tcgetattr(STDIN_FILENO, &data->tty_attr) != 0)
		ft_throw (data, ERR_FAIL, "init gettattr fail", true);
	return (data);
}
