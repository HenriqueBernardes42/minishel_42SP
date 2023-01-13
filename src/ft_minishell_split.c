/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:53:32 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/14 00:50:12 by rburgsta         ###   ########.fr       */
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

void	push_element(t_data *data, t_args3 *args3, char ***tab, bool expand)
{
	char	*element;

	if (args3->i - args3->temp > 1)
	{
		//Debug
		//printf("substr: #%s# %p\n", ft_memdup(args3->str, args3->temp, args3->i), args3->str + args3->temp);
		element = ft_memdup(args3->str, args3->temp, args3->i);
		ft_assert_not_null (data, element);
		if (expand == true)
			ft_expand(data, &element);
		ft_push(data, tab, element);
		free(element);
	}
}

void	push_quotes(t_data *data, t_args3 *args, char ***tab, char c, bool exp)
{
	args->temp = ++args->i;
	while (args->str[args->i] != '\0' && args->str[args->i] != c)
		args->i++;
	push_element(data, args, tab, exp);
	args->i++;
}

static void	ft_handle_type(t_data *data, t_args3 *args3, char ***tab, char *str)
{
	ft_assert_not_null (data, data);
	ft_assert_not_null (data, args3);
	if (ft_istype (&args3->str[args3->i], T_SPECIAL, false))
	{
		args3->temp = args3->i;
		args3->i += ft_istype (&args3->str[args3->i], T_SPECIAL, false);
		push_element(data, args3, tab, false);
	}
	else if (str[args3->i] == '\"')
	{
		printf("#1 %s\n", str + args3->i);
		push_quotes(data, args3, tab, '\"', true);
	}
	else if (str[args3->i] == '\'')
		push_quotes(data, args3, tab, '\'', false);
	else
	{
		args3->temp = args3->i;
		while (str[args3->i] != '\0' && str[args3->i] != ' ')
			args3->i++;
		push_element(data, args3, tab, true);
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
