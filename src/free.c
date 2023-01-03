/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:18:37 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/03 14:51:28 by katchogl         ###   ########.fr       */
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
	if (data->input != NULL)
	{
		i = -1;
		while (data->input[++i] != NULL)
			free (data->input[i]);
		free (data->input);
		data->input = NULL;
	}
}

void	ft_freedata(t_data *data)
{
	if (data == NULL)
		return ;
}
