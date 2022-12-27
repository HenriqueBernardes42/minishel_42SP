/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 06:30:13 by katchogl          #+#    #+#             */
/*   Updated: 2022/12/27 10:19:00 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*If only the first 4 characters of the variable name are compared 
the result of the the matching environment variable could be undefined*/
static void	ft_catchpath_str(t_data *data, char *env, char **path_str)
{
	int		i;
	char	**tab_env;

	ft_assert_not_null (data, env);
	ft_assert_not_null (data, path_str);
	tab_env = ft_split (env, '=');
	if (tab_env != NULL
		&& ft_strncmp ("PATH", tab_env[0], 5) == 0)
		*path_str = ft_strdup (tab_env[1]);
	i = -1;
	while (tab_env[++i] != NULL)
		free (tab_env[i]);
	free (tab_env);
}

void	ft_setpath(t_data *data)
{
	char	*path_str;

	if (data->envp == NULL)
		return ;
	path_str = NULL;
	while (*(data->envp) != NULL)
	{
		ft_catchpath_str (data, *(data->envp)++, &path_str);
		if (path_str != NULL)
			break ;
	}
	if (path_str == NULL)
		return ;
	data->path = ft_split (path_str, ':');
	free (path_str);
}

char	*ft_cmdpath(t_data *data, char *name)
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
