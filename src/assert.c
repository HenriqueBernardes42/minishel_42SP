/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:03:48 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/06 13:48:04 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_assert_not_null(t_data *data, void *ptr)
{
	if (ptr == NULL)
		ft_throw (data, ERR_NULL_PTR, NULL, true);
}

void	ft_assert_not_dir(t_data *data, char *pathname)
{
	int	fd;

	ft_assert_not_null (data, pathname);
	fd = open (pathname, O_DIRECTORY);
	if (fd != -1)
	{
		ft_throw (data, ERR_EISDIR, pathname, true);
		close (fd);
	}
}

static char	*ft_merge(char *path1, char *path2) // TODO: change
{
	char	*path;
	char	*temp;

	if (path1 == NULL)
		return (path2);
	else if (path2 == NULL)
		return (path1);
	if (ft_strlen (path2) == 0)
	{
		free (path2);
		return (path1);
	}
	path = ft_strjoin (path1, "/");
	free (path1);
	temp = ft_strjoin (path, path2);
	free (path2);
	return (temp);
}

void	ft_assert_valid_permissions(t_data *data, char *pathname, int perm)
{
	int		i;
	t_args	*args;

	ft_assert_not_null (data, pathname);
	i = -1;
	args = ft_initargs (data, pathname);
	while (++i < args->count)
	{
		args->path = ft_merge (args->path, args->tab[i]);
		if ((perm == R_OK || (perm == W_OK && i < args->count - 1))
			&& (access (args->path, F_OK) != 0 || access (args->path, perm) != 0))
		{
			if (access (args->path, F_OK) != 0)
				args->err = ENOENT;
			ft_throw (data, args->err, pathname, true);
		}
	}
	free (args->path);
	free (args->tab);
	free (args);
}
