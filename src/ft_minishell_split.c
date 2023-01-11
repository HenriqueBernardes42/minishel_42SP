/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:53:32 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/11 21:15:25 by katchogl         ###   ########.fr       */
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

char	**ft_minishell_split(t_data *data, char *str)
{
	char	**tab;
	int		status;
	size_t	i;
	size_t	temp;
	
	if (str == NULL)
		return (NULL);
	i = 0;
	tab = NULL;
	status = 0;
	while (str[i] != '\0')
	{
		if (ft_istype (&str[i], T_SPECIAL, false) && status == 0)
		{
			ft_push (data, &tab, ft_memdup (str, i,
				i + ft_istype (&str[i], T_SPECIAL, false)));
			i += ft_istype (&str[i], T_SPECIAL, false);
		}
		else if (str[i] != ' ' && status == 0)
		{
			status = 1;
			temp = i;
			i++;
		}
		else if (status != 0
			&& (ft_istype (&str[i], T_SPECIAL, false)
				|| str[i] == ' '))
		{
			ft_push (data, &tab, ft_memdup (str, temp, i));
			status = 0;
		}
		else
			i++;
	}
	if (status == 1)
		ft_push (data, &tab, ft_memdup (str, temp, i));
	return (tab);
}
