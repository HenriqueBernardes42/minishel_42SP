/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:53:32 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/24 17:05:15 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_exec_push_substr_wildcard(t_data *data, char *substr)
{
	int		c;
	int		isredir;

	isredir = false;
	if (ft_tablen (data->tab) > 0)
		isredir = ft_istype (data->tab[ft_tablen (data->tab) - 1],
				T_REDIR, true) != 0;
	c = ft_push_substr_wildcard (data, substr);
	if (c <= 0)
		ft_push (data, &data->tab, substr);
	else if (c > 1 && isredir)
	{
		ft_throw (data, ERR_AMBIGUOUS_REDIRECT, substr, false);
		free (substr);
		return (false);
	}
	return (true);
}

static bool	ft_push_substr(t_data *data, t_args3 *args3, char *str)
{
	char	*wcard_ptr;
	char	*substr;
	bool	expand_wildc;

	substr = ft_memdup (str, args3->temp, args3->i);
	wcard_ptr = ft_strchr (substr, '*');
	expand_wildc = true;
	if (ft_tablen (data->tab) > 0)
		expand_wildc = ft_istype (data->tab[ft_tablen (data->tab) - 1],
				REDIR_HEREDOC, true) == 0;
	if (wcard_ptr != NULL && expand_wildc)
	{
		if (!ft_exec_push_substr_wildcard (data, substr))
			return (false);
	}
	else
		ft_push (data, &data->tab, substr);
	free (substr);
	args3->status = 0;
	return (true);
}

static void	ft_handle_quotes(t_data *data, t_args3 *args3, char *str)
{
	if (str[args3->i] != '\'' && str[args3->i] != '"')
		return ;
	ft_assert_not_null (data, data);
	ft_assert_not_null (data, args3);
	ft_assert_not_null (data, str);
	if (!args3->opened)
	{
		args3->opened = true;
		args3->q = str[args3->i];
	}
	else if (str[args3->i] == args3->q)
	{
		args3->opened = false;
		args3->q = 0;
	}
}

static bool	ft_handle_type(t_data *data, t_args3 *args3, char *str)
{
	ft_assert_not_null (data, data);
	ft_assert_not_null (data, args3);
	if (ft_istype (&str[args3->i], T_SPECIAL, false) && args3->status == 0)
		ft_push_special (data, args3, str);
	else if (args3->status == 1 && (ft_iswhitespace (str[args3->i])
			|| ft_istype (&str[args3->i], T_SPECIAL, false))
		&& !args3->opened)
	{
		if (!ft_push_substr (data, args3, str))
			return (false);
	}
	else if (!ft_iswhitespace (str[args3->i]))
	{
		ft_handle_quotes (data, args3, str);
		if (args3->status == 0)
		{
			args3->status = 1;
			args3->temp = args3->i;
		}
		args3->i++;
	}
	else
		args3->i++;
	return (true);
}

bool	ft_minishell_split(t_data *data, char *str)
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
