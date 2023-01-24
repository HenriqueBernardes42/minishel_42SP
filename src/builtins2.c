/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 20:17:45 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/24 18:17:20 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** 
 * Removes variables from array
 * @param[in] data Minishell data
 * @param[in] args The variables to be removed
 */
void	ft_unset(t_data *data, char **args)
{
	while (args != NULL && *args != NULL)
		ft_remove (data, &data->envp, *ft_get_env_var(data->envp, *args++));
	data->status = EXIT_SUCCESS;
}

/** 
 * Adds a new or replaces an existing env variable
 * @param[in] data Minishell data
 * @param[in] args The variables
 */
void	ft_ar_env_var(t_data *data, char *args)
{
	char	**var;
	char	**env_var;

	var = ft_split(args, '=');
	ft_assert_not_null(data, var);
	if (!ft_valid_env_name(var[0]))
	{
		ft_putinfo ("minishell: export: '", args,
			"': not a valid identifier\n");
		data->status = EXIT_FAILURE;
	}
	env_var = ft_get_env_var(data->envp, var[0]);
	if (*env_var != NULL)
	{
		free(*env_var);
		*env_var = ft_strdup(args);
	}
	else if (ft_valid_env_name(var[0]))
		ft_push(data, &data->envp, args);
	ft_destroy_tab(var);
}

void	ft_export(t_data *data, char **args)
{
	char	**var;
	int		i;

	i = -1;
	data->status = EXIT_SUCCESS;
	if (args == NULL)
	{
		ft_assert_not_null (data, data->envp);
		while (data->envp[++i] != NULL)
		{
			var = ft_split(data->envp[i], '=');
			ft_assert_not_null (data, var);
			printf("declare -x %s=\"%s\"\n", var[0], var[1]);
			ft_destroy_tab(var);
		}
		return ;
	}
	while (args[++i] != NULL)
		if (ft_strchr(args[i], '=') != NULL)
			ft_ar_env_var(data, args[i]);
}

static char	*ft_get_pwd(t_data *data, char *var)
{
	char	*cwd;
	char	*temp;

	cwd = (char *)malloc(MAXPATHLEN + 1);
	ft_assert_not_null(data, cwd);
	if (getcwd(cwd, MAXPATHLEN + 1) == NULL)
	{
		free(cwd);
		ft_throw(data, ERR_FAIL, "cd getcwd null check", true);
	}
	temp = ft_strjoin(var, cwd);
	ft_assert_not_null(data, temp);
	return (free(cwd), temp);
}

void	ft_cd(t_data *data, char *path)
{
	struct stat	fs;
	char		*pwd;

	if (path == NULL)
	{
		path = *ft_get_env_var(data->envp, "HOME");
		if (path != NULL)
			path += 5;
		else
			ft_putstr_fd ("minishell: cd: HOME not set\n", STDERR_FD);
	}
	pwd = ft_get_pwd(data, "OLDPWD=");
	stat (path, &fs);
	if (path != NULL && !S_ISDIR (fs.st_mode))
		ft_putinfo ("minishell: cd: ", path, ": Not a directory\n");
	else if (path != NULL && chdir(path))
		ft_putinfo ("minishell: cd: ", path, ": No such file or directory\n");
	else if (path != NULL)
		ft_ar_env_var(data, pwd);
	data->status = (path == NULL || !S_ISDIR (fs.st_mode) || chdir(path));
	free(pwd);
	pwd = ft_get_pwd(data, "PWD=");
	ft_ar_env_var(data, pwd);
	free(pwd);
}
