/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 21:37:57 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/06 13:25:59 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_args	*ft_initargs(t_data *data, char *pathname)
{
	t_args	*args;
	int		i;

	args = (t_args *) malloc (sizeof (t_args));
	ft_assert_not_null (data, args);
	args->count = 0;
	if (pathname != NULL)
	{
		args->tab = ft_split (pathname, '/');
		if (pathname[0] == '/')
			args->path = ft_strdup ("/");
		i = -1;
		while (args->tab[++i] != NULL)
			args->count++;
	}
	else
	{
		args->tab = NULL;
		args->path = NULL;
	}
	args->err = EACCES;
	return (args);
}

t_cmd	*ft_initcmds(t_data *data, int cmdsc)
{
	t_cmd	*cmds;
	int		i;
	
	if (cmdsc < 0)
		ft_throw (data, ERR_INVALID_CMDSC, NULL, true);
	cmds =  (t_cmd *) malloc (cmdsc * sizeof (t_cmd));
	ft_assert_not_null (data, cmds);
	i = -1;
	while (++i < cmdsc)
	{
		cmds[i].name = NULL;
		cmds[i].pathname = NULL;
		cmds[i].args = NULL;
		cmds[i].redir_args = NULL;
		cmds[i].redirs = NULL;
		cmds[i].redirsc = 0;
	}
	return (cmds);
}

t_data 	*ft_initdata(char **envp)
{
	t_data	*data;

	data = (t_data *) malloc (sizeof (t_data));
	ft_assert_not_null (data, data);
	data->envp = envp;
	data->path = ft_split (getenv ("PATH"), ':');
	data->line = NULL;
	data->tab = NULL;
	data->cmds = NULL;
	data->cmdsc = -1;
	data->pipes = NULL;
	return (data);
}
