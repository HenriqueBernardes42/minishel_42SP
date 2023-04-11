/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdelone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhenriqu <hhenriqu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:47:12 by hhenriqu          #+#    #+#             */
/*   Updated: 2023/02/17 16:05:55 by hhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstdelone(t_dlist *dlst_node, void (*del)(void*))
{
	if (del)
		del(dlst_node->content);
	free(dlst_node);
	dlst_node = NULL;
}
