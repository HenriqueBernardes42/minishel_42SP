/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhenriqu <hhenriqu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 04:49:25 by hhenriqu          #+#    #+#             */
/*   Updated: 2023/04/15 17:44:56 by hhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_assert_finished(t_data *data)
{
	char	*linepl;

	if (data == NULL || data->line == NULL || data->tab == NULL)
		ft_throw (data, ERR_NULL_PTR, NULL, true);
	while (!ft_isfinished (data))
	{
		linepl = readline ("> ");
		if (linepl == NULL)
			return (ft_throw (data, ERR_UNEXPECTED_EOF, NULL, false));
		else if (ft_strncmp (linepl, "", 1) != 0)
		{
			ft_update_line (data, linepl);
			free (linepl);
			ft_remove_last_history (data);
			ft_addhistory (data, data->line);
			ft_destroy_tab (data->tab);
			data->tab = NULL;
			if (!ft_minishell_split (data, data->line) || !ft_isvalid (data))
				return (false);
		}
	}
	return (true);
}

void	ft_assert_not_null(t_data *data, void *ptr)
{
	if (ptr == NULL)
		ft_throw (data, ERR_NULL_PTR, NULL, true);
}

bool	ft_assert_not_dir(t_data *data, char *pathname, bool exitp)
{
	struct stat	file_stat;

	ft_assert_not_null (data, pathname);
	stat (pathname, &file_stat);
	if (S_ISDIR (file_stat.st_mode))
	{
		if (data->status == 0)
			data->status = EXIT_EXECUTABLE_PERM_DENIED;
		ft_throw (data, ERR_EISDIR, NULL, exitp);
		return (false);
	}
	return (true);
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

bool	ft_assert_valid_permissions(t_data *data, char *pathname, int permss,
	bool exitp)
{
	int		i;
	t_args	*args;

	ft_assert_not_null (data, pathname);
	args = ft_initargs (data, pathname);
	i = -1;
	while (++i < args->count)
	{
		ft_mkpath (args, pathname, i);
		if (ft_is_permission_denied (args, permss, i))
		{
			if (access (args->path, F_OK) != 0)
				args->err = ERR_ENOENT;
			if (data->status == 0)
				data->status = EXIT_EXECUTABLE_PERM_DENIED;
			ft_throw (data, args->err, pathname, exitp);
			return (false);
		}
	}
	ft_destroy_args (args);
	return (true);
}
