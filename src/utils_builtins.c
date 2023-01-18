/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:25:56 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/17 21:30:17 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_builtin(t_data *data, int i, char *builtin)
{
	if (ft_strncmp (builtin, "echo", 5) == 0)
		ft_echo (data, data->cmds[i].args);
	else if (ft_strncmp (builtin, "cd", 3) == 0)
	{
		if (data->cmds[i].argsc > 0)
			ft_cd (data, data->cmds[i].args[0]);
		else
			ft_cd (data, NULL);
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

bool	ft_valid_env_name(char *str)
{
	int	i;

	if (ft_strlen(str) < 1)
		return (false);
	i = -1;
	while (str[++i] != '\0')
	{
		if (!i && ft_isdigit(str[i]))
			return (false);
		else if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (false);
	}
	return (true);
}

/** 
 * Searches an array for a variable
 * @param[in] envp The array to be searched
 * @param[in] var The name of the variable that will be searched for
 * @return Pointer to the variable if found otherwise pointer to 
 * the end of the array
 */
char	**ft_get_env_var(char **envp, char *var)
{
	int	i;
	int	len;

	len = ft_strlen(var);
	i = -1;
	while (envp[++i] != NULL)
		if (!ft_strncmp(var, envp[i], len) && envp[i][len] == '=')
			return (envp + i);
	return (envp + i);
}
