/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:39:17 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/09 17:57:36 by rburgsta         ###   ########.fr       */
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
