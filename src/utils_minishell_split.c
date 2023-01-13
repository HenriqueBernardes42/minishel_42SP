/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell_split.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:29:52 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/13 13:58:16 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getcwd(t_data *data)
{
	char	*cwd;

	cwd = (char *) malloc ((MAXPATHLEN + 1) * sizeof (char));
	if (cwd == NULL)
		ft_throw (data, ERR_FAIL, "malloc", true);
	if (getcwd (cwd, MAXPATHLEN + 1) == NULL)
	{
		free(cwd);
		return (NULL);
	}
	return (cwd);
}

bool ft_matches_pattern(char *pattern, char *filename)
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
