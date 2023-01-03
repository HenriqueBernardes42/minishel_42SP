/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 21:37:57 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/03 22:08:01 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		cmds[i].infiles = NULL;
		cmds[i].heredoc_lims = NULL;
		cmds[i].outfiles_trc = NULL;
		cmds[i].outfiles_app = NULL;
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
	return (data);
}
