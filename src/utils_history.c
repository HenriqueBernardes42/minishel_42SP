/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:04:58 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/20 19:18:16 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_addhistory(t_data *data, char *line)
{
	ft_assert_not_null (data, data);
	ft_assert_not_null (data, line);
	add_history (line);
	ft_push (data, &data->history, line);
	data->where_history++;
}

void	ft_remove_last_history(t_data *data)
{
	int		i;
	char	**nhistory;

	if (data->history == NULL || data->where_history == 0)
		return ;
	nhistory = NULL;
	i = -1;
	clear_history ();
	data->where_history--;
	while (++i < data->where_history)
	{
		ft_push (data, &nhistory, data->history[i]);
		add_history (data->history[i]);
	}
	ft_destroy_tab (data->history);
	data->history = nhistory;
}
