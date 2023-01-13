/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 21:53:44 by rburgsta          #+#    #+#             */
/*   Updated: 2023/01/13 21:53:44 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_insert_var(t_data *data, char **tab, int index)
{
	char	*str;
	char	*var;
	int		i;

	i = (ft_isdigit((*tab)[index]) || tab[0][index] == '?');
	if (i == 0)
		while ((ft_isalnum((*tab)[index + i]) || tab[0][index + i] == '_') && tab[0][index + i] != '\'')
			i++;
	var = ft_substr(*tab, index, i);
	if ((*tab)[index] == '?')
		str = ft_itoa(data->ret_pipe);
	else if (*get_env_var(data->envp, var) != NULL)
		str = *get_env_var(data->envp, var) + ft_strlen(var) + 1;
	else
		str = "";
	free(var);
	var = (char *)malloc(ft_strlen(*tab) + ft_strlen(str));
	ft_strlcpy(var, *tab, index);
	ft_strlcat(var, str, ft_strlen(*tab) + ft_strlen(str));
	ft_strlcat(var, *tab + index + i, ft_strlen(*tab) - ft_strlen(str) + 1);
	if ((*tab)[index] == '?')
		free(str);
	free(*tab);
	*tab = var;
}

void	remove_char(t_data *data, char **str, int index)
{
	char	*temp;

	temp = (char *)malloc(ft_strlen(*str));
	ft_assert_not_null(data, temp);
	ft_strlcpy(temp, *str, index + 1);
	ft_strlcat(temp, *str + index + 1, ft_strlen(*str));
	free(*str);
	*str = temp;
}

void	ft_expand(t_data *data, char **str)
{
	int	i;
	bool	expand;

	ft_assert_not_null (data, data);
	ft_assert_not_null (data, str);
	i = -1;
	expand = true;
	while ((*str)[++i] != '\0')
	{
		if (expand && (*str)[i] == '\'')
		{
			remove_char(data, str, i--);
			expand = !expand;
			continue ;
		}
		else if (expand && (*str)[i] == '\"')
		{
			remove_char(data, str, i--);
			continue ;
		}
		if ((*str)[i] == '$' && (*str)[i + 1] != ' '
			&& (*str)[i + 1] != '\0' && expand == true)
			ft_insert_var(data, str, i + 1);
	}
}
