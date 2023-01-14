/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:03:48 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/14 14:31:25 by rburgsta         ###   ########.fr       */
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

/// @brief Assert that a pointer is not null.
/// @param data The minishell's data;
/// @param ptr The pointer.
void	ft_assert_not_null(t_data *data, void *ptr)
{
	if (ptr == NULL)
		ft_throw (data, ERR_NULL_PTR, NULL, true);
}

/// @brief Assert that a file is not a directory.
/// @param data The minishell's data;
/// @param pathname The pathname.
bool	ft_assert_not_dir(t_data *data, char *pathname, bool exitp)
{
	struct stat	file_stat;

	ft_assert_not_null (data, pathname);
	stat (pathname, &file_stat);
	if (S_ISDIR (file_stat.st_mode) && exitp == true)
		ft_throw (data, ERR_EISDIR, NULL, true);
	else if (S_ISDIR(file_stat.st_mode))
		return (false);
	return (true);
		
}

/// @brief Join the pathnane by far with the additional one.
/// @param args The struct of argumentsof type
/// s_args2 dedicated to the function;
/// @param pathname The additional pathname;
/// @param i The index of the filename in the split of
/// the additonal pathname.
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

/// @brief Assert that the user has the correct permissions
/// to access a file and also that the file exists.
/// @param data The minishell's data;
/// @param pathname The pathname;
/// @param permss The permission to check: either R_OK or W_OK from unistd.h.
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
		if ((permss == R_OK || (permss == W_OK && i < args->count - 1))
			&& (access (args->path, F_OK) != 0
				|| access (args->path, permss) != 0))
		{
			if (access (args->path, F_OK) != 0)
				args->err = ERR_ENOENT;
			ft_throw (data, args->err, pathname, true);
		}
	}
	if (args->path != NULL)
		free (args->path);
	if (args->tab != NULL)
		ft_destroy_tab (args->tab);
	free (args);
}
