/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhenriqu <hhenriqu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:47:05 by hhenriqu          #+#    #+#             */
/*   Updated: 2023/02/17 16:06:00 by hhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstclear(t_dlist **lst, void (*del)(void*))
{
	t_dlist	*tmp;
	t_dlist	*begin;

	if (lst)
	{
		begin = *lst;
		while (*lst)
		{
			tmp = (*lst)->next;
			ft_dlstdelone(*lst, del);
			(*lst) = tmp;
			if (*lst == begin)
				break ;
		}
	}
}
