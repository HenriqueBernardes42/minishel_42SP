/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 11:27:41 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/14 14:39:55 by rburgsta         ###   ########.fr       */
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
		ft_remove (data, &data->envp, *get_env_var(data->envp, *args++));
	data->ret_pipe = EXIT_SUCCESS;
}

/** 
 * Adds a new or replaces an existing env variable
 * @param[in] data Minishell data
 * @param[in] args The variables
 */
static void	ar_env_var(t_data *data, char *args)
{
	char	**var;
	char	**env_var;

	var = ft_split(args, '=');
	ft_assert_not_null(data, var);
	if (!valid_env_name(var[0]))
	{
		printf("minishell: export: '%s': not a valid identifier\n", args);
		data->ret_pipe = EXIT_FAILURE;
	}
	env_var = get_env_var(data->envp, var[0]);
	if (*env_var != NULL)
	{
		free(*env_var);
		*env_var = ft_strdup(args);
	}
	else if (valid_env_name(var[0]))
		ft_push(data, &data->envp, args);
	ft_destroy_tab(var);
}

void	ft_export(t_data *data, char **args)
{
	char	**var;
	int		i;

	i = -1;
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
			ar_env_var(data, args[i]);
}

static void update_pwd(t_data *data)
{
	char	*cwd;
	char	*temp;

	cwd = (char *)malloc(MAXPATHLEN + 1);
	ft_assert_not_null(data, cwd);
	if (getcwd(cwd, MAXPATHLEN + 1) == NULL)
		ft_throw(data, ERR_FAIL, "cd getcwd null check", true);
	temp = ft_strjoin("PWD=", cwd);
	ar_env_var(data, temp);
	free(temp);
	free(cwd);
}

void	ft_cd(t_data *data, char *path)
{
	if (path == NULL)
	{
		path = *get_env_var(data->envp, "HOME");
		if (path != NULL)
			path += 5;
		else
			printf("minishell: cd: HOME not set\n");
	}
	if (path != NULL && ft_assert_not_dir(data, path, false))
		printf("minishell: cd: %s: Not a directory\n", path);
	else if (path != NULL && chdir(path))
		printf("minishell: cd: %s: No such file or directory\n", path);
	update_pwd(data);
}
