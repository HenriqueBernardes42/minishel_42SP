/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstfirst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhenriqu <hhenriqu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:47:18 by hhenriqu          #+#    #+#             */
/*   Updated: 2023/02/17 16:05:53 by hhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstfirst(t_dlist *dlst)
{
	if (!dlst)
		return (0);
	while (dlst->prev)
		dlst = dlst->prev;
	return (dlst);
}
