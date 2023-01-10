/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 11:27:41 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/10 11:45:19 by rburgsta         ###   ########.fr       */
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
char **get_env_var(char **envp, char *var)
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
 * @param[in] args The variables that will be removed
 */
void	ft_unset(t_data *data, char **args) // parent process, ptr freed not alloc
{
	while (args != NULL && *args != NULL)
		ft_remove (data, &data->envp, *get_env_var(data->envp, *args++));
}

bool valid_env_name(char *str)
{
	int i;

	if (ft_strlen(str) < 1)
		return (false);
	i = -1;
	while (str[++i] != '\0')
	{
		if (!i && ft_isdigit(str[i]))
			return (false);
		else if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (false);
	}
	return (true);
}

void	ft_export(t_data *data, char **args) // parent process, ptr freed not alloc
{
	char	**var;
	char	*env_var;
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
	{
		if (ft_strchr(*args, '=') != NULL)
		{
			var = ft_split(*args, '=');
			if (!valid_env_name(var[0]))
				printf("bash: export: '%s': not a valid identifier\n", *args);
			env_var = *get_env_var(data->envp, var[0]);
			free(env_var);
			if (valid_env_name(var[0]) && env_var != NULL)
				env_var = ft_strdup(*args);
			else if (valid_env_name(var[0]))
				ft_push(data, &data->envp, *args);
			ft_destroy_tab(var);
		}
		args++;
	}
}

void	ft_cd(t_data *data, char *path) // try in parent
{
	char	*cwd;
	char	*temp;

	if (path == NULL)
	{
		path = *get_env_var(data->envp, "HOME");
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
		ft_remove(data, &data->envp, *get_env_var(data->envp, "PWD"));
		ft_push(data, &data->envp, temp);
		free(temp);
		free(cwd);
	}
}
