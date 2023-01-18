/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell_split.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:29:52 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/18 13:36:13 by katchogl         ###   ########.fr       */
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

static int	ft_strchri(const char *s, int c)
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

bool	ft_matches_pattern(char *pattern, char *filename)
{
	int	i;
	int	j;

	if (pattern == NULL || filename == NULL)
		return (false);
	if (ft_strchri (pattern, '*') > 0)
	{
		i = -1;
		while (pattern[++i] != '*')
			if (pattern[i] != filename[i])
				return (false);
	}
	if (ft_strchri (pattern, '*') < (int) ft_strlen (pattern) - 1
		&& ft_strchri (pattern, '*') != -1)
	{
		i = ft_strlen (pattern);
		j = ft_strlen (filename);
		while (pattern[--i] != '*')
			if (pattern[i] != filename[--j])
				return (false);
	}
	return (true);
}

void	ft_push_special(t_data *data, t_args3 *args3, char *str)
{
	char	*substr;

	substr = ft_memdup (str, args3->i, args3->i
			+ ft_istype (&str[args3->i], T_SPECIAL, false));
	ft_push (data, &data->tab, substr);
	free (substr);
	args3->i += ft_istype (&str[args3->i], T_SPECIAL, false);
}
