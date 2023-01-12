/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:03:48 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/12 10:24:17 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_assert_finished(t_data *data)
{
	char	*linepl;
	char	*temp;

	ft_assert_not_null (data, data);
	ft_assert_not_null (data, data->line);
	ft_assert_not_null (data, data->tab);
	while (ft_istype (data->tab[ft_tablen (data->tab) - 1], T_OP, true)
		|| ft_istype (data->tab[ft_tablen (data->tab) - 1], T_PIPE, true))
	{
		linepl = readline ("> ");
		temp = ft_strjoin (data->line, " ");
		free (data->line);
		data->line = ft_strjoin (temp, linepl);
		free (temp);
		free (linepl);
		ft_destroy_tab (data->tab);
		data->tab = ft_minishell_split (data, data->line);
		if (!ft_isvalid (data))
			return (false);
	}
	return (true);
}

void	ft_assert_not_null(t_data *data, void *ptr)
{
	if (ptr == NULL)
		ft_throw (data, ERR_NULL_PTR, NULL, true);
}

void	ft_assert_not_dir(t_data *data, char *pathname)
{
	struct stat	file_stat;

	stat (pathname, &file_stat);
	if (S_ISDIR (file_stat.st_mode))
		ft_throw (data, ERR_EISDIR, NULL, true);
}

static void	ft_mkpath(t_args *args, char *pathname, int i)
{
	if (args->path == NULL)
	{
		if (pathname[0] != '/')
			args->path = ft_strdup (args->tab[i]);
		else
			args->path = ft_strjoin ("/", args->tab[i]);
	}
	else
	{
		args->temp = ft_strjoin (args->path, "/");
		free (args->path);
		args->path = args->temp;
		args->temp = ft_strjoin (args->path, args->tab[i]);
		free (args->path);
		args->path = args->temp;
	}
}

void	ft_assert_valid_permissions(t_data *data, char *pathname, int permss)
{
	int		i;
	t_args	*args;

	ft_assert_not_null (data, pathname);
	args = ft_initargs (data, pathname);
	i = -1;
	while (++i < args->count)
	{
		ft_mkpath (args, pathname, i);
		if (access (args->path, F_OK) != 0
			&& (permss == R_OK || (permss == W_OK && i < args->count - 1)))
			ft_throw (data, ERR_ENOENT, pathname, true);
		else if (access (args->path, permss) != 0 && (permss == R_OK
				|| (permss == W_OK && access (args->path, F_OK) == 0)))
			ft_throw (data, ERR_EACCES, pathname, true);
	}
	if (args->path != NULL)
		free (args->path);
	if (args->tab != NULL)
		ft_destroy_tab (args->tab);
	free (args);
}
