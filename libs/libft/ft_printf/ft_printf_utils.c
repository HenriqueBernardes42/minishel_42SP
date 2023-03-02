/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhenriqu <hhenriqu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:26:19 by hhenriqu          #+#    #+#             */
/*   Updated: 2023/02/17 15:26:20 by hhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_num_len(unsigned int n, int base)
{
	int	i;

	i = 1;
	n /= base;
	while (n)
	{
		i++;
		n /= base;
	}
	return (i);
}

int	ft_num_len_int(int n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		i += 1;
		n *= -1;
	}
	n /= 10;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

void	ft_handle_zero_dot(unsigned int n, int *num_len, t_flags *flags)
{
	if (flags->f_zero > flags->p_dot && flags->p_dot < *num_len
		&& flags->p_dot != -1)
		flags->f_width = flags->f_zero;
	if (flags->f_zero > flags->p_dot && flags->p_dot > *num_len
		&& flags->p_dot != -1)
		flags->f_width = flags->f_zero - (flags->p_dot - *num_len);
	if (!n && !flags->p_dot)
		*num_len = 0;
}
