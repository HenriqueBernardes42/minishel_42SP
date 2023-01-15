/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_assert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:01:11 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/15 14:01:12 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_notify_line_changed(t_data *data)
{
	struct _hist_entry	*entry;

	if (where_history () >= 0)
	{
		entry = remove_history (where_history () - 1);
		if (entry != NULL)
		{
			free (entry->line);
			free (entry->data);
			free (entry);
		}
	}
	add_history (data->line);
}

void	ft_linejoin(t_data *data, char *linepl)
{
	char	*temp;
	
	temp = ft_strjoin (data->line, " ");
	free (data->line);
	data->line = ft_strjoin (temp, linepl);
	free (temp);
}

static void	ft_notify_f_found(int *c, char *f, char chr)
{
	(*c)++;
	if (*f == 0)
		*f = chr;
	if (*c == 2)
	{
		*c = 0;
		*f = 0;
	}
}

bool ft_all_apostroph_closed(t_data *data)
{
	int	c;
	int	i;
	int	j;
	char f;
	
	ft_assert_not_null (data, data);
	ft_assert_not_null (data, data->tab);
	i = -1;
	c = 0;
	f = 0;
	while (data->tab[++i] != NULL)
	{
		j = -1;
		while (data->tab[i][++j] != '\0')
			if ((data->tab[i][j] == '\'' || data->tab[i][j] == '\"')
				&& (f == 0 || f == data->tab[i][j]))
				ft_notify_f_found (&c, &f, data->tab[i][j]);
	}
	return (c % 2 == 0);
}
