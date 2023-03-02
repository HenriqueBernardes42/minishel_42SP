/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_resolve_chr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhenriqu <hhenriqu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:26:28 by hhenriqu          #+#    #+#             */
/*   Updated: 2023/02/17 17:53:47 by hhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_put_space_chr(int n_spaces)
{
	while (n_spaces)
	{
		ft_putchar_fd(' ', 1);
		n_spaces--;
	}
	return (0);
}

int	ft_resolve_chr(char c, t_flags flags)
{
	int	len;

	len = 1;
	if (flags.f_width)
	{
		ft_put_space_chr(flags.f_width - 1);
		len += (flags.f_width - 1);
	}
	ft_putchar_fd(c, 1);
	if (flags.f_minus)
	{
		ft_put_space_chr(flags.f_minus - 1);
		len += (flags.f_minus - 1);
	}
	return (len);
}
