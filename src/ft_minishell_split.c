/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:53:32 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/13 17:15:53 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_memdup(char const *s, size_t a, size_t b)
{
	char	*ptr;
	int		i;

	if (b - a <= 0)
		return (NULL);
	ptr = (char *) malloc ((b - a + 1) * sizeof (char));
	i = -1;
	while (a < b)
	{
		ptr[++i] = s[a];
		a++;
	}
	ptr[++i] = '\0';
	return (ptr);
}

static void	ft_insert_var(t_data *data, char **tab, int index)
{
	char	*str;
	char	*var;
	int		i;

	i = (ft_isdigit((*tab)[index]) || tab[0][index] == '?');
	if (i == 0)
		while (ft_isalnum((*tab)[index + i]) || tab[0][index + i] == '_')
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

void	ft_expand(t_data *data, char **str)
{
	int	i;

	ft_assert_not_null (data, data);
	ft_assert_not_null (data, str);
	i = -1;
	while ((*str)[++i] != '\0')
	{
		if ((*str)[i] == '$' && (*str)[i + 1] != ' ' && (*str)[i + 1] != '\0')
			ft_insert_var(data, str, i + 1);
	}
}

void	push_element(t_data *data, t_args3 *args3, char ***tab, bool expand)
{
	char	*element;

	if (args3->temp < args3->i)
	{
		printf("substr: #%s# %p\n", ft_memdup(args3->str, args3->temp, args3->i), args3->str + args3->temp);
		element = ft_memdup(args3->str, args3->temp, args3->i);
		ft_assert_not_null (data, element);
		if (expand == true)
			ft_expand(data, &element);
		ft_push(data, tab, element);
		free(element);
	}
	args3->status = 0;
}

static void	ft_handle_type(t_data *data, t_args3 *args3, char ***tab, char *str)
{
	ft_assert_not_null (data, data);
	ft_assert_not_null (data, args3);
	if (ft_istype (&str[args3->i], T_SPECIAL, false))
	{
		args3->temp = args3->i;
		args3->i += ft_istype (&str[args3->i], T_SPECIAL, false);
		push_element(data, args3, tab, false);
	}
	else if (str[args3->i] == '\"' && args3->status == 0)
	{
		args3->temp = ++args3->i;
		while (str[args3->i] != '\0' && str[args3->i] != '\"')
			args3->i++;
		push_element(data, args3, tab, true);
	}
	else if (str[args3->i] == '\'' && args3->status == 0)
	{
		args3->temp = ++args3->i;
		while (str[args3->i] != '\0' && str[args3->i] != '\'')
			args3->i++;
		push_element(data, args3, tab, false);
	}
	else
	{
		args3->temp = args3->i;
		while (str[args3->i] != '\0' && str[args3->i] != ' ')
		{
			if (ft_istype (&str[args3->i], T_SPECIAL, false) && !args3->status)
				break ;
			args3->i++;
		}
		push_element(data, args3, tab, true);
		args3->status = 0;
	}
}

char	**ft_minishell_split(t_data *data, char *str)
{
	t_args3	*args3;
	char	**tab;

	if (str == NULL)
		return (NULL);
	tab = NULL;
	args3 = ft_initargs3 (data, str);
	while (str[args3->i] != '\0')
	{
		while (str[args3->i] != '\0' && str[args3->i] == ' ')
			args3->i++;
		if (str[args3->i] != '\0')
			ft_handle_type (data, args3, &tab, str);
	}
	free (args3);
	return (tab);
}
