/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhenriqu <hhenriqu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:33:37 by hhenriqu          #+#    #+#             */
/*   Updated: 2023/02/17 15:33:38 by hhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long int	ft_atol(const char *str)
{
	long int	num;
	int			sig;

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
