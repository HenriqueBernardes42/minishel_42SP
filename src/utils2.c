/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:19:49 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/09 19:50:08 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isbuiltin(char *str)
{
	if (str == NULL)
		return (false);
	if (ft_strncmp (str, "echo", 5) == 0
		|| ft_strncmp (str, "pwd", 4) == 0
		|| ft_strncmp (str, "env", 4) == 0)
		return (1);
	else if (ft_strncmp (str, "exit", 5) == 0 
		|| ft_strncmp (str, "export", 8) == 0
		|| ft_strncmp (str, "unset", 7) == 0
		|| ft_strncmp (str, "cd", 3) == 0)
		return (2);
	return (0);
}

void	ft_builtin(t_data *data, int i, char *builtin)
{
	if (ft_strncmp (builtin, "echo", 5) == 0)
		ft_echo (data->cmds[i].args);
	else if (ft_strncmp (builtin, "cd", 3) == 0)
	{
		if (data->cmds[i].argsc > 1)
			ft_cd (data, data->cmds[i].args[0]);
		else
			ft_cd (data, NULL); // go to user root dir (~/)
	}
	else if (ft_strncmp (builtin, "pwd", 4) == 0)
		ft_pwd (data);
	else if (ft_strncmp (builtin, "export", 8) == 0)
		ft_export (data, data->cmds[i].args);
	else if (ft_strncmp (builtin, "unset", 7) == 0)
		ft_unset (data, data->cmds[i].args);
	else if (ft_strncmp (builtin, "env", 4) == 0)
		ft_env(data);
	else if (ft_strncmp (builtin, "exit", 5) == 0)
		ft_exit (data, data->cmds[i].args);
}
