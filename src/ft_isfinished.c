/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isfinished.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 15:15:02 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/21 15:15:58 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_all_parenth_closed(t_data *data)
{
	int	c;
	int	i;

	ft_assert_not_null(data, data);
	c = 0;
	i = -1;
	while (data->tab[++i] != NULL)
	{
		if (ft_istype (data->tab[i], T_PARENTH_OPEN, true))
			c++;
		else if (ft_istype (data->tab[i], T_PARENTH_CLOSE, true))
			c--;
	}
	return (c == 0);
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

static bool	ft_all_apostroph_closed(t_data *data)
{
	int		c;
	int		i;
	int		j;
	char	f;

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

bool	ft_isfinished(t_data *data)
{
	if (ft_istype (data->tab[ft_tablen (data->tab) - 1], T_OP, true)
		|| ft_istype (data->tab[ft_tablen (data->tab) - 1], T_PIPE, true)
		|| !ft_all_parenth_closed (data)
		|| !ft_all_apostroph_closed (data))
		return (false);
	return (true);
}
