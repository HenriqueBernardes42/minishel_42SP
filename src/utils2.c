/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:56:25 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/24 18:20:36 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_iswhitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v'
		|| c == '\n' || c == '\r' || c == '\f')
		return (true);
	return (false);
}

void	ft_update_shlvl(t_data *data)
{
	int		i;
	char	*shlvl;
	char	*val;

	i = 0;
	shlvl = getenv("SHLVL");
	if (shlvl == NULL)
		shlvl = "SHLVL=1";
	else
	{
		while (shlvl[i] != '\0')
			if (!ft_isdigit(shlvl[i++]))
				break ;
		if (i == 0 || shlvl[i] != '\0')
			shlvl = "SHLVL=1";
		else
		{
			val = ft_itoa(ft_atoi(shlvl) + 1);
			shlvl = ft_strjoin("SHLVL=", val);
			free(val);
		}
	}
	ft_ar_env_var(data, shlvl);
	if (i != 0 && getenv("SHLVL") != NULL && shlvl[i + 6] == '\0')
		free(shlvl);
}
