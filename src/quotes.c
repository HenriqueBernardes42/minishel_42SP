/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhenriqu <hhenriqu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 02:06:42 by hhenriqu          #+#    #+#             */
/*   Updated: 2023/04/15 19:15:35 by hhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_single_quotes(char *line)

{
	int		i;
	char	quote;
	int		open;

	i = 0;
	open = 0;
	while (line[i] != '\0')
	{
		if ((line[i] == '\"' || line[i] == '\'') && open == 0)
		{
			quote = line[i];
			open++;
			i++;
		}
		else if (line[i] == quote && open == 1)
		{
			open = 0;
			i++;
		}
		else
			i++;
	}
	return (open);
}
