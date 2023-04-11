/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhenriqu <hhenriqu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 02:43:03 by hhenriqu          #+#    #+#             */
/*   Updated: 2023/04/11 02:43:04 by hhenriqu         ###   ########.fr       */
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
