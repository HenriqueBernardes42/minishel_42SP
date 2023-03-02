/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhenriqu <hhenriqu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:36:05 by hhenriqu          #+#    #+#             */
/*   Updated: 2023/02/17 14:36:06 by hhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

char	*ft_getenv(char *var)
{
	t_dlist	*head;
	char	*tmp;

	head = g_msh.envp_lst;
	while (head->next != NULL)
	{
		head = head->next;
		tmp = head->content;
		if (!ft_strncmp(head->content, var, ft_strlen(var)) \
		&& !ft_strncmp(tmp + ft_strlen(var), "=", 1))
			return (head->content + ft_strlen(var) + 1);
	}
	return ("\0");
}

static void	print(void *varenv)
{
	printf("%s\n", (char *)varenv);
}

int	env(void)
{
	ft_dlstiter(g_msh.envp_lst, &print);
	return (0);
}
