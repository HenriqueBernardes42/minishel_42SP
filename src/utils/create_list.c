/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhenriqu <hhenriqu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:33:11 by hhenriqu          #+#    #+#             */
/*   Updated: 2023/02/17 14:33:14 by hhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

t_dlist	*create_list(char **strs)
{
	t_dlist	*envp_lst;
	int		i;

	envp_lst = NULL;
	i = -1;
	while (strs[++i])
		if (ft_strnstr(strs[i], "WORKSPACE", ft_strlen(strs[i])) == NULL)
			ft_dlstadd_back(&envp_lst, ft_dlstnew((void *)ft_strdup(strs[i])));
	return (envp_lst);
}

char	*get_node_value(t_dlist *node)
{
	return ((char *)node->content);
}
