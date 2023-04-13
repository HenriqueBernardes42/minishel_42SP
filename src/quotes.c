/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhenriqu <hhenriqu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 02:06:42 by hhenriqu          #+#    #+#             */
/*   Updated: 2023/04/13 02:20:19 by hhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_single_quotes(char *line, char quote)

{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (line[i] != '\0')
	{
		if (line[i] == quote)
		{
			quotes++;
			i++;
		}
		i++;
	}
	if (quotes % 2 == 0)
		return (0);
	else
		return (1);
}
