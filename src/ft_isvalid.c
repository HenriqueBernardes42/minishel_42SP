/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isvalid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:02:19 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/21 12:15:57 by rburgsta         ###   ########.fr       */
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
	int		i;
	int		opened;

	ft_assert_not_null (data, data);
	ft_assert_not_null (data, data->tab);
	i = -1;
	opened = 0;
	while (data->tab[++i] != NULL)
	{
		if (!ft_isvalidpl (data, i) || !ft_isvalidpl2
			(data, i, &opened) || !ft_isvalidpl3 (data, i, &opened))
		{
			data->status = EXIT_UNEXPECTED_TOKEN;
			return (false);
		}		
	}
	return (true);
}
