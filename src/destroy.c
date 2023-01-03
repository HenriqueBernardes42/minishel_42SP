/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 21:40:47 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/03 22:08:36 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_destroy_execution (t_data *data)
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
		free (data->cmds);
		data->cmds = NULL;
	}
	data->cmdsc = -1;
}

void	ft_destroy_data(t_data *data)
{
	int	i;
	
	if (data == NULL)
		return ;
	ft_destroy_execution (data);
	if (data->path != NULL)
	{
		i = -1;
		while (data->path[++i] != NULL)
			free (data->path[i]);
		free (data->path);
	}
	free (data);
}
