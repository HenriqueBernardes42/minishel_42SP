/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:53:32 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/12 16:26:08 by katchogl         ###   ########.fr       */
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

static void	ft_handle_type(t_data *data, t_args3 *args3, char ***tab, char *str)
{
	ft_assert_not_null (data, data);
	ft_assert_not_null (data, args3);
	if (ft_istype (&str[args3->i], T_SPECIAL, false) && args3->status == 0)
	{
		ft_push (data, tab, ft_memdup (str, args3->i,
				args3->i + ft_istype (&str[args3->i], T_SPECIAL, false)));
		args3->i += ft_istype (&str[args3->i], T_SPECIAL, false);
	}
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
		ft_push (data, tab, ft_memdup (str, args3->temp, args3->i));
		args3->status = 0;
	}
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
		ft_push (data, &tab, ft_memdup (str, args3->temp, args3->i));
	free (args3);
	return (tab);
}
