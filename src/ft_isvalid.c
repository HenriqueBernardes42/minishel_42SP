/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isvalid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:02:19 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/15 14:40:48 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_isvalidpl3(t_data *data, int i, int *opened)
{
	if (ft_istype (data->tab[i], T_CMD_SEP, true)
		&& *opened > 0)
		return (ft_throw (data, ERR_UNEXPECTED_TOKEN,
				data->tab[i], false));
	else if (ft_istype (data->tab[i], T_CMD_CAT, true)
		&& (i == 0 || ft_istype (data->tab[i - 1], T_CMD_CAT, true)))
		return (ft_throw (data, ERR_UNEXPECTED_TOKEN,
				data->tab[i], false));
	else if (ft_istype (data->tab[i], T_CMD_SEP, true)
		&& data->tab[i + 1] != NULL)
		return (ft_throw (data, ERR_UNEXPECTED_TOKEN,
				data->tab[i + 1], false));
	else if (ft_strncmp (data->tab[i], "\\", 2) == 0)
		return (ft_throw (data, ERR_UNEXPECTED_TOKEN,
				data->tab[i], false));
	return (true);
}

static bool	ft_isvalidpl2(t_data *data, int i, int *opened)
{
	if (ft_istype (data->tab[i], T_PARENTH_OPEN, true))
		(*opened)++;
	else if (ft_istype (data->tab[i], T_PARENTH_CLOSE, true))
	{
		ft_putnbr_fd (*opened, 2);
		if (*opened == 0 || ft_istype (data->tab[i - 1], T_PIPE, true))
			return (ft_throw (data, ERR_UNEXPECTED_TOKEN,
					data->tab[i], false));
		else
			(*opened)--;
	}
	return (true);
}

static bool	ft_isvalidpl(t_data *data, int i)
{
	if (ft_istype (data->tab[i], T_REDIR, true))
	{
		if (data->tab[i + 1] == NULL)
			return (ft_throw (data, ERR_UNEXPECTED_TOKEN,
					"(null)", false));
		else if (ft_istype (data->tab[i + 1], T_SPECIAL, true))
			return (ft_throw (data, ERR_UNEXPECTED_TOKEN,
					data->tab[i + 1], false));
	}
	return (true);
}

bool	ft_isvalid(t_data *data)
{
	int	i;
	int	opened;
	int	opened2;

	ft_assert_not_null (data, data);
	ft_assert_not_null (data, data->tab);
	i = -1;
	opened = 0;
	opened2 = false;
	while (data->tab[++i] != NULL)
	{
		if (!opened2 && (!ft_isvalidpl (data, i) || !ft_isvalidpl2
				(data, i, &opened) || !ft_isvalidpl3 (data, i, &opened)))
			return (false);
	}
	return (true);
}
