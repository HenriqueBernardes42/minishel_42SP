/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 21:37:57 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/12 11:52:56 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*ft_initpipes(t_data *data, int cmdsc)
{	
	int	*pipes;
	int	i;

	if (cmdsc < 2)
		return (NULL);
	pipes = (int *) malloc ((cmdsc - 1) * 2 * sizeof (int));
	if (pipes == NULL)
		ft_throw (data, ERR_FAIL, "malloc", true);
	i = -1;
	while (++i < cmdsc - 1)
		if (pipe (pipes + i * 2) != 0)
			ft_throw (data, ERR_FAIL, "fail", true);
	return (pipes);
}

t_args2	*ft_initargs2(t_data *data, int i, t_fd *infd, t_fd *outfd)
{
	t_args2	*args2;

	ft_assert_not_null (data, data->cmds);
	if (i >= data->cmdsc)
		ft_throw (data, ERR_INVALID_CMDSC, NULL, true);
	args2 = (t_args2 *) malloc (sizeof (t_args2));
	ft_assert_not_null (data, args2);
	args2->i = i;
	args2->j = data->cmds[i].redirsc;
	args2->infd = infd;
	args2->outfd = outfd;
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
		cmds[i].inst = I_UNDEF;
	}
	return (cmds);
}

t_data	*ft_initdata(char **envp)
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
