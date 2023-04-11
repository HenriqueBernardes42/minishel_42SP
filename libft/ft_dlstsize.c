/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstsize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhenriqu <hhenriqu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:47:47 by hhenriqu          #+#    #+#             */
/*   Updated: 2023/02/17 16:06:17 by hhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dlstsize(t_dlist *dlst)
{
	int	i;

	if (!dlst)
		return (0);
	i = 1;
	while (dlst->next)
	{
		dlst = dlst->next;
		i++;
	}
	return (i);
}
