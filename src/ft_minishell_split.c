/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:53:32 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/13 15:55:02 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_push_special(t_data *data, t_args3 *args3, char *str)
{
	char	*substr;

	substr = ft_memdup (str, args3->i, args3->i
			+ ft_istype (&str[args3->i], T_SPECIAL, false));
	ft_push (data, &data->tab, substr);
	free (substr);
	args3->i += ft_istype (&str[args3->i], T_SPECIAL, false);
}

static int	ft_push_substr_wildcard(t_data *data, char *pattern)
{
	DIR				*dir;
	struct dirent	*ent;
	int				c;

	c = 0;
	dir = opendir (".");
	if (dir != NULL)
	{
		ent = readdir (dir);
		while (ent != NULL)
		{
			if ((ft_strncmp ("*", pattern, 2) == 0
					|| ft_matches_pattern (pattern, ent->d_name))
				&& (ent->d_name[0] != '.'))
			{
				ft_push (data, &data->tab, ent->d_name);
				c++;
			}
			ent = readdir (dir);
		}
		closedir (dir);
	}
	return (c);
}

static bool	ft_push_substr(t_data *data, t_args3 *args3, char *str)
{
	int		c;
	char	*wcard_ptr;
	char	*substr;
	bool	isredir;

	substr = ft_memdup (str, args3->temp, args3->i);
	wcard_ptr = ft_strchr (substr, '*');
	if (wcard_ptr != NULL)
	{
		isredir = false;
		if (ft_tablen (data->tab) > 0)
			isredir = ft_istype (data->tab[ft_tablen (data->tab) - 1],
				T_REDIR, true) != 0;
		c = ft_push_substr_wildcard (data, substr);
		if (c <= 0)
			ft_push (data, &data->tab, substr);
		else if (c > 0 && isredir)
		{
			ft_throw (data, ERR_AMBIGUOUS_REDIRECT, substr, false);
			free (substr);
			return (false);
		}
	}
	else
		ft_push (data, &data->tab, substr);
	free (substr);
	args3->status = 0;
	return (true);
}

static bool	ft_handle_type(t_data *data, t_args3 *args3, char *str)
{
	ft_assert_not_null (data, data);
	ft_assert_not_null (data, args3);
	if (ft_istype (&str[args3->i], T_SPECIAL, false) && args3->status == 0)
		ft_push_special (data, args3, str);
	else if (str[args3->i] != ' ' && args3->status == 0)
	{
		args3->status = 1;
		args3->temp = args3->i;
		args3->i++;
	}
	else if (args3->status == 1
		&& (ft_istype (&str[args3->i], T_SPECIAL, false)
			|| str[args3->i] == ' '))
		{
			if (!ft_push_substr (data, args3, str))
				return (false);
		}
	else
		args3->i++;
	return (true);
}

bool ft_minishell_split(t_data *data, char *str)
{
	t_args3	*args3;

	if (str == NULL)
		return (NULL);
	args3 = ft_initargs3 (data);
	while (str[args3->i] != '\0')
		if (!ft_handle_type (data, args3, str))
			return (false);
	if (args3->status == 1)
		if (!ft_push_substr (data, args3, str))
			return (false);
	free (args3);
	return (true);
}
