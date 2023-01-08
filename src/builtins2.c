/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 11:27:41 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/08 13:58:49 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **get_env_var(char **envp, char *var)
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

void	ft_unset(t_data *data, char **args)
{
	while (*args != NULL)
		ft_remove (data, &data->envp, *get_env_var(data->envp, *args++));
	exit (EXIT_SUCCESS);
}

void	ft_export(t_data *data, char **args)
{
	char	**var;
	char	*env_var;
	int		i;

	i = -1;
	if (*args == NULL)
	{
		while (data->envp[++i] != NULL)
		{
			var = ft_split(data->envp[i], '=');
			printf("declare -x %s=\"%s\"\n", var[0], var[1]);
			ft_destroy_tab(var);
		}
	}
	while (*args != NULL)
	{
		if (ft_strchr(*args, '=') != NULL)
		{
			var = ft_split(*args, '=');
			env_var = *get_env_var(data->envp, var[0]);
			free(env_var);
			if (env_var != NULL)
				env_var = ft_strdup(*args);
			else
				ft_push(data, &data->envp, *args);
			ft_destroy_tab(var);
		}
		else
		{
			//if (*get_env_var(data->envp, var[0]) != NULL)
				//Add env variable to 'export env' list
		}
		args++;
	}
	exit (EXIT_SUCCESS);
}

void	ft_cd(t_data *data, char *path)
{
	char	**env_loc;
	char	*cwd;

	env_loc = get_env_var(data->envp, "PWD");
	if (chdir(path))
		printf("bash: cd: %s: No such file or directory\n", path);
	else
	{
		cwd = (char *)malloc(MAXPATHLEN + 1);
		if (cwd == NULL)
			ft_throw (data, ERR_FAIL, "cd cwd malloc", true);
		else if (getcwd(cwd, MAXPATHLEN + 1) == NULL)
		{
			free(cwd);
			ft_throw (data, ERR_FAIL, "cd getcwd null check", true);
		}
		//free(*env_loc);
		*env_loc = ft_strjoin("PWD=", cwd);
		free(cwd);
	}
	exit (EXIT_SUCCESS);
}
