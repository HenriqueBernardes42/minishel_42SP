/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 11:27:41 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/13 10:03:38 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** 
 * Searches an array for a variable
 * @param[in] envp The array to be searched
 * @param[in] var The name of the variable that will be searched for
 * @return Pointer to the variable if found otherwise pointer to 
 * the end of the array
 */
char	**ft_get_env_var(char **envp, char *var)
{
	int	i;
	int	len;

	len = ft_strlen(var);
	i = -1;
	while (envp[++i] != NULL)
		if (!ft_strncmp(var, envp[i], len) && envp[i][len] == '=')
			return (envp + i);
	return (envp + i);
}

/** 
 * Removes variables from array
 * @param[in] data Minishell data
 * @param[in] args The variables to be removed
 */
void	ft_unset(t_data *data, char **args)
{
	while (args != NULL && *args != NULL)
		ft_remove (data, &data->envp, *ft_get_env_var(data->envp, *args++));
}

/** 
 * Adds a new or replaces an existing env variable
 * @param[in] data Minishell data
 * @param[in] args The variables
 */
static void	ft_ar_env_var(t_data *data, char **args)
{
	char	**var;
	char	*env_var;

	var = ft_split(*args, '=');
	if (!ft_valid_env_name(var[0]))
		printf("bash: export: '%s': not a valid identifier\n", *args);
	env_var = *ft_get_env_var(data->envp, var[0]);
	free(env_var);
	if (ft_valid_env_name(var[0]) && env_var != NULL)
		env_var = ft_strdup(*args);
	else if (ft_valid_env_name(var[0]))
		ft_push(data, &data->envp, *args);
	ft_destroy_tab(var);
}

void	ft_export(t_data *data, char **args)
{
	char	**var;
	int		i;

	i = -1;
	if (args == NULL)
	{
		while (data->envp[++i] != NULL)
		{
			var = ft_split(data->envp[i], '=');
			printf("declare -x %s=\"%s\"\n", var[0], var[1]);
			ft_destroy_tab(var);
		}
		return ;
	}
	while (*args != NULL)
		if (ft_strchr(*args++, '=') != NULL)
			ft_ar_env_var(data, args - 1);
}

void	ft_cd(t_data *data, char *path)
{
	char	*cwd;
	char	*temp;

	if (path == NULL)
	{
		path = *ft_get_env_var(data->envp, "HOME");
		if (path != NULL)
			path += 5;
		else
			printf("bash: cd: HOME not set\n");
	}
	if (path != NULL && chdir(path))
		printf("bash: cd: %s: No such file or directory\n", path);
	else if (path != NULL)
	{
		cwd = NULL;
		if (getcwd(cwd, MAXPATHLEN + 1) == NULL)
			ft_throw (data, ERR_FAIL, "cd getcwd null check", true);
		temp = ft_strjoin("PWD=", cwd);
		ft_remove(data, &data->envp, *ft_get_env_var(data->envp, "PWD"));
		ft_push(data, &data->envp, temp);
		free(temp);
		free(cwd);
	}
}
