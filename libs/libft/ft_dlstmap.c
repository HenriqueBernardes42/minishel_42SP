/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhenriqu <hhenriqu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:47:35 by hhenriqu          #+#    #+#             */
/*   Updated: 2023/02/17 16:05:44 by hhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstmap(t_dlist *dlst, void *(*f)(void *), void (*del)(void *))
{
	t_dlist	*new;
	t_dlist	*begin;

	if (dlst)
	{
		begin = ft_dlstnew(f(dlst->content));
		if (!begin)
			return (NULL);
		dlst = dlst->next;
		while (dlst)
		{
			new = ft_dlstnew(f(dlst->content));
			if (!new)
			{
				ft_dlstclear(&begin, del);
				return (NULL);
			}
			ft_dlstadd_back(&begin, new);
			dlst = dlst->next;
		}
		return (begin);
	}
	return (NULL);
}
