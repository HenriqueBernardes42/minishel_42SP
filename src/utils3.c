/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 10:53:00 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/14 13:39:33 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	valid_env_name(char *str)
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
char	**get_env_var(char **envp, char *var)
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