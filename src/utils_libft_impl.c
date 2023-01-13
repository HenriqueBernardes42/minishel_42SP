/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft_impl.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:27:31 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/13 14:26:00 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_memdup(char const *s, size_t a, size_t b)
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

int	ft_strchri(const char *s, int c)
{
	int	i;

	i = -1;
	if (c == 0)
		return (ft_strlen (s));
	while (s[++i])
		if (s[i] == (const char) c)
			return (i);
	return (-1);
}
