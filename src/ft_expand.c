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

static void	remove_quote(t_data *data, bool *quote, char **str, int index)
{
	char	*temp;
	int		i;

	i = index + 1;
	while ((*str)[i] != '\0' && (*str)[i] != (*str)[index])
		i++;
	if ((*str)[i] != '\0')
		*quote = !*quote;
	temp = (char *)malloc(ft_strlen(*str));
	ft_assert_not_null(data, temp);
	ft_strlcpy(temp, *str, index + 1);
	ft_strlcat(temp, *str + index + 1, ft_strlen(*str));
	free(*str);
	*str = temp;
}

static void	ft_insert_var(t_data *data, char **tab, int index)
{
	char	*str;
	char	*var;
	int		i;

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
	var = (char *)malloc(ft_strlen(*tab) + ft_strlen(str));
	ft_strlcpy(var, *tab, index);
	ft_strlcat(var, str, ft_strlen(*tab) + ft_strlen(str));
	ft_strlcat(var, *tab + index + i, ft_strlen(*tab) - ft_strlen(str) + 1);
	if ((*tab)[index] == '?')
		free(str);
	free(*tab);
	*tab = var;
}

void ft_expand_str(t_data *data, char **str)
{
	int		i;
	bool	double_quote;
	bool	single_quote;

	i = -1;
	double_quote = false;
	single_quote = false;
	while ((*str)[++i] != '\0')
	{
		if (!double_quote && (*str)[i] == '\'')
			remove_quote(data, &single_quote, str, i--);
		else if (!single_quote && (*str)[i] == '\"')
			remove_quote(data, &double_quote, str, i--);
		else if ((*str)[i] == '$' && (*str)[i + 1] != '\0' && !single_quote)
			ft_insert_var(data, str, i-- + 1);
	}
	//Debug
	printf("'%s' ", *str);
}

/// @brief 
/// @param data 
/// @param tab The arguments
void	ft_expand_tab(t_data *data, char **tab)
{
	int	i;

	if (tab == NULL)
		return ;
	i = -1;
	//Debug
	printf("DEBUG: output: ft_expand_tab: ");
	while (tab[++i] != NULL)
		ft_expand_str(data, tab + i);
	
	printf("\n");
}
