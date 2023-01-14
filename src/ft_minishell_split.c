/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:53:32 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/14 12:41:23 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_memdup(char const *s, size_t a, size_t b)
{
	char	*ptr;
	int		i;

	if (b - a < 0)
		return (NULL);
	ptr = (char *) malloc ((b - a + 1) * sizeof (char));
	if (ptr == NULL)
		return (NULL);
	i = -1;
	while (a < b)
	{
		ptr[++i] = s[a];
		a++;
	}
	ptr[++i] = '\0';
	return (ptr);
}

static void	push_argument(t_data *data, t_args3 *args, char ***tab, bool expand)
{
	char	*argument;

	// Debug
	// printf("substr: #%s# %p\n", ft_memdup(args3->str, args3->temp, args3->i), args3->str + args3->temp);
	argument = ft_memdup(args->str, args->temp, args->i);
	ft_assert_not_null(data, argument);
	if (expand == true)
		ft_expand(data, args, &argument);
	ft_push(data, tab, argument);
	free(argument);
}

// void	push_quotes(t_data *data, t_args3 *args, char ***tab, char c)
// {
// 	args->temp = args->i++;
// 	while (args->str[args->i] != '\0' && args->str[args->i] != c)
// 		args->i++;
// 	args->i++;
// 	push_argument(data, args, tab, !args->single_quote);
// 	args->single_quote = false;
// 	args->double_quote = false;
// }

static void	ft_handle_type(t_data *data, t_args3 *args3, char ***tab)
{
	ft_assert_not_null (data, data);
	ft_assert_not_null (data, args3);
	args3->temp = args3->i;
	if (ft_istype (&args3->str[args3->i], T_SPECIAL, false))
	{
		args3->i += ft_istype (&args3->str[args3->i], T_SPECIAL, false);
		push_argument(data, args3, tab, false);
		return ;
	}
	while (args3->str[args3->i] != '\0' && ((args3->str[args3->i] != ' '
				&& !ft_istype(&args3->str[args3->i], T_SPECIAL, false))
			|| args3->single_quote || args3->double_quote))
	{
		if (args3->str[args3->i] == '\"')
			args3->double_quote = !args3->double_quote;
		else if (args3->str[args3->i] == '\'')
			args3->single_quote = !args3->single_quote;
		args3->i++;
	}
	args3->double_quote = false;
	args3->single_quote = false;
	push_argument(data, args3, tab, true);
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
			ft_handle_type (data, args3, &tab);
	}
	free (args3);
	return (tab);
}
