/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:31:01 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/17 14:31:01 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_remove_quote(t_data *data, bool *quote, char **str, int index)
{
	char	*temp;

	if (quote != NULL)
		*quote = !*quote;
	temp = (char *)malloc(ft_strlen(*str));
	ft_assert_not_null(data, temp);
	ft_strlcpy(temp, *str, index + 1);
	ft_strlcat(temp, *str + index + 1, ft_strlen(*str));
	free(*str);
	*str = temp;
}

static bool	ft_istype_xp(char *substr, bool s_quote,
	bool d_quote, t_expand_str_type type)
{
	if (type == T_ENV && *substr == '$' && !s_quote
		&& (ft_isalnum (*(substr + 1)) || *(substr + 1) == '_'
			|| *(substr + 1) == '?'))
		return (true);
	else if (type == T_HOME && *substr == '~'
		&& (*(substr + 1) == '/' || *(substr + 1) == '\0')
		&& !s_quote && !d_quote)
		return (true);
	return (false);
}

void	ft_expand_str(t_data *data, char **str, char ***tab, int arg_i)
{
	int		i;
	bool	d_quote;
	bool	s_quote;
	int		c;

	i = -1;
	d_quote = false;
	s_quote = false;
	while (*str != NULL && (*str)[++i] != '\0')
	{
		if (!d_quote && (*str)[i] == '\'')
			ft_remove_quote(data, &s_quote, str, i--);
		else if (!s_quote && (*str)[i] == '\"')
			ft_remove_quote(data, &d_quote, str, i--);
		else if (ft_istype_xp ((*str) + i, s_quote, d_quote, T_ENV))
		{
			c = ft_insert_var(data, str, i-- + 1);
			if (!d_quote && tab != NULL && arg_i != -1 && (*str)[i + 1]
				&& ft_explode_env (data, &str, tab, ft_initargsxp
					(data, i + 1, c, &arg_i)))
				i = -1;
		}
		else if (ft_istype_xp ((*str) + i, s_quote, d_quote, T_HOME))
			ft_insert_home_dir(data, str, i-- + 1);
	}
}

void	ft_expand_tab(t_data *data, char ***tab)
{
	int	i;

	if (tab == NULL)
		ft_throw (data, ERR_NULL_PTR, NULL, true);
	else if (*tab == NULL)
		return ;
	i = -1;
	while ((*tab)[++i] != NULL)
		ft_expand_str(data, (*tab) + i, tab, i);
}
