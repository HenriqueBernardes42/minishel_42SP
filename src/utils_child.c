/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:46:58 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/17 23:49:16 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_explode_name(t_data *data, int i)
{
	char	**tab;
	int		j;
	
	ft_assert_not_null (data, data);
	ft_assert_not_null (data, data->cmds);
	if (data->cmds[i].name == NULL)
		return ;
	tab = ft_split (data->cmds[i].name, ' ');
	if (tab != NULL)
	{
		if (ft_tablen (tab) > 1)
		{
			j = ft_tablen (tab);
			while (--j > 0)
				ft_shift (data, &data->cmds[i].args, tab[j]);
			free (data->cmds[i].name);
			data->cmds[i].name = ft_strdup (tab[0]);
		}
		ft_destroy_tab (tab);
	}
}
