/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_assert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:01:11 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/15 13:13:34 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
