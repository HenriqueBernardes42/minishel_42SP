/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 19:58:43 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/07 17:41:24 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pathname(t_data *data, char *name)
{
	int		i;
	char	*dir;
	char	*pathname;

	ft_assert_not_null (data, data);
	ft_assert_not_null (data, name);
	if (access (name, X_OK) != -1)
		return (ft_strdup (name));
	i = -1;
	if (data->path == NULL)
		return (NULL);
	while (data->path[++i] != NULL)
	{
		dir = ft_strjoin (data->path[i], "/");
		pathname = ft_strjoin (dir, name);
		free (dir);
		if (access (pathname, X_OK) != -1)
			return (pathname);
		free (pathname);
	}
	return (NULL);
}

t_redir	ft_getredir(char *str)
{
	if (ft_strncmp (str, "<", 2) == 0)
		return (REDIR_INFILE);
	else if (ft_strncmp (str, ">", 2) == 0)
		return (REDIR_OUTFILE_TRC);
	else if (ft_strncmp (str, "<<", 3) == 0)
		return (REDIR_HEREDOC);
	else if (ft_strncmp (str, ">>", 3) == 0)
		return (REDIR_OUTFILE_APP);
	return (REDIR_UNDEF);
}
