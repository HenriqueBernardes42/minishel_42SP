/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:53:32 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/13 12:37:14 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_push_special(t_data *data, t_args3 *args3, char ***tab,
	char *str)
{
	char	*substr;
	
	substr = ft_memdup (str, args3->i, args3->i 
		+ ft_istype (&str[args3->i], T_SPECIAL, false));
	ft_push (data, tab, substr);
	free (substr);
	args3->i += ft_istype (&str[args3->i], T_SPECIAL, false);
}

static int ft_push_substr_wildcard(t_data *data,
	char ***tab, char *pattern)
{
	DIR				*dir;
	struct dirent	*ent;
	char			*cwd;
	int				c;

	c = 0;
	cwd = ft_getcwd (data);
	if (cwd != NULL)
	{
		dir = opendir (cwd);
		if (dir != NULL)
		{
			ent = readdir (dir);
			while (ent != NULL)
			{
				if ((ft_strncmp ("*", pattern, 2) == 0
					|| ft_matches_pattern (pattern, ent->d_name))
					&& ent->d_name[0] != '.')
				{
					ft_push (data, tab, ent->d_name);
					c++;
				}
				ent = readdir (dir);
			}
			closedir (dir);
		}
		free (cwd);
	}
	return (c);
}

static void	ft_push_substr(t_data *data, t_args3 *args3, char ***tab,
	char *str)
{
	char	*wcard_ptr;
	char	*substr;
	
	substr = ft_memdup (str, args3->temp, args3->i);
	wcard_ptr = ft_strchr (substr, '*');
	if (wcard_ptr != NULL)
	{
		if (ft_push_substr_wildcard (data, tab, substr) <= 0)
			ft_push (data, tab, substr);
	}
	else
		ft_push (data, tab, substr);
	free (substr);
	args3->status = 0;
}

static void	ft_handle_type(t_data *data, t_args3 *args3, char ***tab, char *str)
{
	ft_assert_not_null (data, data);
	ft_assert_not_null (data, args3);
	if (ft_istype (&str[args3->i], T_SPECIAL, false) && args3->status == 0)
		ft_push_special (data, args3, tab, str);
	else if (str[args3->i] != ' ' && args3->status == 0)
	{
		args3->status = 1;
		args3->temp = args3->i;
		args3->i++;
	}
	else if (args3->status == 1
		&& (ft_istype (&str[args3->i], T_SPECIAL, false)
			|| str[args3->i] == ' '))
		ft_push_substr (data, args3, tab, str);
	else
		args3->i++;
}

char	**ft_minishell_split(t_data *data, char *str)
{
	t_args3	*args3;
	char	**tab;

	if (str == NULL)
		return (NULL);
	args3 = ft_initargs3 (data);
	tab = NULL;
	while (str[args3->i] != '\0')
		ft_handle_type (data, args3, &tab, str);
	if (args3->status == 1)
		ft_push_substr (data, args3, &tab, str);
	free (args3);
	return (tab);
}
