/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:39:17 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/10 14:16:45 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

bool	ft_istype(char *str, t_type type)
{
	if (str == NULL)
		return (false);
	if (ft_strncmp (str, "<", 2) == 0
		&& (type == T_SPECIAL || type == T_REDIR))
		return (true);
	else if (ft_strncmp (str, "<<", 3) == 0
		&& (type == T_SPECIAL || type == T_REDIR))
		return (true);
	else if (ft_strncmp (str, ">", 2) == 0
		&& (type == T_SPECIAL || type == T_REDIR))
		return (true);
	else if (ft_strncmp (str, ">>", 3) == 0
		&& (type == T_SPECIAL || type == T_REDIR))
		return (true);
	else if (ft_strncmp (str, ";", 2) == 0
		&& (type == T_SPECIAL || type == T_CMD_SEP))
		return (true);
	else if (ft_strncmp (str, "|", 2) == 0
		&& (type == T_SPECIAL || type == T_PIPE))
		return (true);
	return (false);
}

bool valid_env_name(char *str)
{
	int i;

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