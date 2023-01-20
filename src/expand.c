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

static int	ft_insert_var(t_data *data, char **tab, int index)
{
	char	*str;
	char	*var;
	int		i;
	int		c;

	i = (ft_isdigit((*tab)[index]) || tab[0][index] == '?');
	if (i == 0)
		while ((ft_isalnum((*tab)[index + i]) || (*tab)[index + i] == '_'))
			i++;
	var = ft_substr(*tab, index, i);
	if ((*tab)[index] == '?')
		str = ft_itoa(data->status);
	else if (*ft_get_env_var(data->envp, var) != NULL)
		str = *ft_get_env_var(data->envp, var) + ft_strlen(var) + 1;
	else
		str = "";
	free(var);
	var = (char *)malloc(ft_strlen(*tab) + ft_strlen(str) + 1);
	ft_strlcpy(var, *tab, index);
	ft_strlcat(var, str, ft_strlen(*tab) + ft_strlen(str) + 1);
	ft_strlcat(var, *tab + index + i, ft_strlen(*tab) + ft_strlen(str) + 1);
	c = ft_strlen (str);
	if ((*tab)[index] == '?')
		free(str);
	free(*tab);
	*tab = var;
	return (c);
}

void ft_expand_str(t_data *data, char **str, char ***tab, int arg_i)
{
	int		i;
	bool	double_quote;
	bool	single_quote;
	int		c;

	i = -1;
	double_quote = false;
	single_quote = false;
	while (*str != NULL && (*str)[++i] != '\0')
	{
		if (!double_quote && (*str)[i] == '\'')
			ft_remove_quote(data, &single_quote, str, i--);
		else if (!single_quote && (*str)[i] == '\"')
			ft_remove_quote(data, &double_quote, str, i--);
		else if ((*str)[i] == '$' && !single_quote
			&& (ft_isalnum((*str)[i + 1]) || (*str)[i + 1] == '_'
				|| (*str)[i + 1] == '?'))
		{
			c = ft_insert_var(data, str, i-- + 1);
			if (!double_quote && tab != NULL
				&& arg_i != -1 && (*str)[i + 1] )
			{
				if (ft_cut_str (data, &str, tab, 
					ft_initargsxp (data, i, c, &arg_i)))
					i = -1;
			}
		}
		else if ((*str)[i] == '~'
			&& ((*str)[i + 1] == '/' || (*str)[i + 1] == '\0')
			&& !single_quote && !double_quote)
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
