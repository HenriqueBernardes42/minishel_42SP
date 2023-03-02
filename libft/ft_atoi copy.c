/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi copy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhenriqu <hhenriqu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 20:17:39 by hhenriqu          #+#    #+#             */
/*   Updated: 2023/02/19 20:17:40 by hhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	num;
	int	sig;

	num = 0;
	sig = 1;
	while (ft_isspace(*str))
		str++;
	if (ft_isdigit(*str) || *str == '-' || *str == '+')
	{
		if (*str == '-')
			sig = -1;
		if (*str == '+' || *str == '-')
			str++;
		while (ft_isdigit(*str))
		{
			num *= 10;
			num += *str - '0';
			str++;
		}
	}
	return (num * sig);
}
