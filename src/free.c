/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:18:37 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/03 20:01:16 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_freeinput(t_data *data)
{
	int	i;
	
	if (data->line != NULL)
	{
		free (data->line);
		data->line = NULL;
	}
	if (data->tab != NULL)
	{
		i = -1;
		while (data->tab[++i] != NULL)
			free (data->tab[i]);
		free (data->tab);
		data->tab = NULL;
	}
	if (data->cmds != NULL)
	{
		i = -1;
		while (data->cmds[++i] != NULL)
			free (data->cmds[i]);
		free (data->cmds);
		data->cmds = NULL;
	}
}

void	ft_freedata(t_data *data)
{
	if (data == NULL)
		return ;
}
