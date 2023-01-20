/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tab2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:43:18 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/19 18:43:32 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_subtab(t_data *data, char **tab, unsigned int start, int len)
{
	char	**subtab;
	int	i;

	if (tab == NULL)
		return (NULL);
	subtab = NULL;
	i = start;
	while (i < (int) start + len)
	{
		ft_push (data, &subtab, tab[i]);
		i++;
	}
	return (subtab);
}
