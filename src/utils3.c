/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 10:53:00 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/12 11:53:45 by katchogl         ###   ########.fr       */
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
