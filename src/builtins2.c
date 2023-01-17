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
static void	ft_ar_env_var(t_data *data, char *args)
{
	char	**var;
	char	**env_var;

	var = ft_split(args, '=');
	ft_assert_not_null(data, var);
	if (!ft_valid_env_name(var[0]))
	{
		printf("minishell: export: '%s': not a valid identifier\n", args);
		data->status = EXIT_FAILURE;
	}
	else if (ft_strchr(args, '=') != NULL)
	{
		env_var = ft_get_env_var(data->envp, var[0]);
		if (*env_var != NULL)
		{
			free(*env_var);
			*env_var = ft_strdup(args);
		}
		else if (ft_valid_env_name(var[0]))
			ft_push(data, &data->envp, args);
	}
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
		ft_ar_env_var(data, args[i]);
}

static void ft_update_pwd(t_data *data)
{
	char	*cwd;
	char	*temp;

	cwd = (char *)malloc(MAXPATHLEN + 1);
	ft_assert_not_null(data, cwd);
	if (getcwd(cwd, MAXPATHLEN + 1) == NULL)
		ft_throw(data, ERR_FAIL, "cd getcwd null check", true);
	temp = ft_strjoin("PWD=", cwd);
	ft_ar_env_var(data, temp);
	free(temp);
	free(cwd);
}

void	ft_cd(t_data *data, char *path)
{
	data->status = EXIT_FAILURE;
	if (path == NULL)
	{
		path = *ft_get_env_var(data->envp, "HOME");
		if (path != NULL)
			path += 5;
		else
			printf("minishell: cd: HOME not set\n");
	}
	if (path != NULL && ft_assert_not_dir(data, path, false))
		printf("minishell: cd: %s: Not a directory\n", path);
	else if (path != NULL && chdir(path))
		printf("minishell: cd: %s: No such file or directory\n", path);
	else if (path != NULL)
		data->status = EXIT_SUCCESS;
	ft_update_pwd(data);
}