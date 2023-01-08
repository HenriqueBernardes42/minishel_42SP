/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 11:56:09 by rburgsta          #+#    #+#             */
/*   Updated: 2023/01/04 11:56:09 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include "../libft/libft.h"
#include <string.h>
#include <sys/param.h>

typedef enum e_errno {
	ERR_UNDEF,
	ERR_NULL_CHECK_FAIL,
	ERR_MALLOC_FAIL,
	ERR_PIPE_FAIL,
	ERR_FORK_FAIL,
	ERR_ENOENT,
	ERR_UNEXPECTED_TOKEN,
	ERR_INVALID_CMDSC,
	ERR_C
} t_errno;
typedef	struct s_cmd
{
	char	*name;
	char	*pathname;
	char	**args;
	char	**infiles;
	char	**heredoc_lims;
	char	**outfiles_trc;
	char	**outfiles_app;
} t_cmd;
typedef struct s_data
{
	char	**envp;
	char	**path;
	char	*line;
	char	**tab;
	t_cmd	*cmds;
	int		cmdsc;
}	t_data;

bool	ft_throw(t_data *data, enum e_errno err, char *info, bool exitp);

void	ft_assert_not_null(t_data *data, void *ptr)
{
	if (ptr == NULL)
		ft_throw (data, ERR_NULL_CHECK_FAIL, NULL, true);
}

t_data 	*ft_initdata(char **envp)
{
	t_data	*data;

	data = (t_data *) malloc (sizeof (t_data));
	ft_assert_not_null (data, data);
	data->envp = envp;
	data->path = ft_split (getenv ("PATH"), ':');
	data->line = NULL;
	data->tab = NULL;
	data->cmds = NULL;
	data->cmdsc = -1;
	return (data);
}

void	ft_destroy_tab(char **tab)
{
	int	i;

	if (tab == NULL)
		return ;
	i = -1;
	while (tab[++i] != NULL)
		free (tab[i]);
	free (tab);
}

static void	ft_destroy_cmds(t_data *data)
{
	int	i;
	
	if (data == NULL || data->cmds == NULL)
		return ;
	i = -1;
	while (++i < data->cmdsc)
	{
		if (data->cmds[i].name != NULL)
			free (data->cmds[i].name);
		if (data->cmds[i].pathname != NULL)
			free (data->cmds[i].pathname);
		if (data->cmds[i].args != NULL)
			ft_destroy_tab (data->cmds[i].args);
		if (data->cmds[i].infiles != NULL)
			ft_destroy_tab (data->cmds[i].infiles);
		if (data->cmds[i].heredoc_lims != NULL)
			ft_destroy_tab (data->cmds[i].heredoc_lims);
		if (data->cmds[i].outfiles_trc != NULL)
			ft_destroy_tab (data->cmds[i].outfiles_trc);
		if (data->cmds[i].outfiles_app != NULL)
			ft_destroy_tab (data->cmds[i].outfiles_app);
	}
	free (data->cmds);
}

void	ft_destroy_execution (t_data *data)
{
	if (data->line != NULL)
	{
		free (data->line);
		data->line = NULL;
	}
	if (data->tab != NULL)
	{
		ft_destroy_tab (data->tab);
		data->tab = NULL;
	}
	if (data->cmds != NULL)
	{
		ft_destroy_cmds (data);
		data->cmds = NULL;
	}
	data->cmdsc = -1;
}

void	ft_destroy_data(t_data *data)
{
	if (data == NULL)
		return ;
	ft_destroy_execution (data);
	if (data->path != NULL)
		ft_destroy_tab (data->path);
	free (data);
}

bool	ft_throw(t_data *data, enum e_errno err, char *info, bool exitp)
{
	char	**errors;

	errors = (char *[ERR_C]){"an error occurred", "null pointer",
		"failed to allocate heap memory", "pipe fail", "fork fail",
		strerror (ERR_ENOENT), "syntax error near unexpected token",
		"invalid commands' count"};
	printf ("minishell: ");
	if (info != NULL && err == ERR_ENOENT)
		printf ("%s ", info);
	if (err >= ERR_UNDEF && err < ERR_C)
		printf ("%s", errors[err]);
	else
		printf ("an unexpected error occurred");
	if (info != NULL && err == ERR_UNEXPECTED_TOKEN)
		printf (" `%s'", info);
	if (info != NULL && err != ERR_UNEXPECTED_TOKEN
		&& err != ERR_ENOENT)
		printf (": `%s'", info);
	printf ("\n\033[0m");
	if (exitp)
	{
		ft_destroy_data (data);
		exit (EXIT_FAILURE);
	}
	return (false);
}

void	ft_push(t_data *data, char ***tab, char *str)
{
	char	**ntab;
	int		size_tab;
	int		i;
	
	if (str == NULL)
		return ;
	size_tab = 0;
	if (*tab != NULL)
	{
		i = -1;
		while ((*tab)[++i] != NULL)
			size_tab++;
	}
	ntab = (char **) malloc ((size_tab + 2) * sizeof (char *));
	if (ntab == NULL)
		ft_throw (data, ERR_NULL_CHECK_FAIL, "ft_push ntab", true);
	i = -1;
	while (++i < size_tab)
		ntab[i] = ft_strdup ((*tab)[i]);
	ntab[i] = ft_strdup (str);
	ntab[i + 1] = NULL;
	ft_destroy_tab (*tab);
	*tab = ntab;
}

void	ft_pull(t_data *data, char ***tab, char *str)
{
	char	**ntab;
	int		size_tab;
	int		i;
	
	if (str == NULL)
		return ;
	size_tab = 0;
	i = -1;
	if (*tab != NULL)
		while ((*tab)[++i] != NULL)
			if (ft_strncmp(str, (*tab)[i], ft_strlen(str) + 1))
				size_tab++;
	ntab = (char **)malloc((size_tab + 1) * sizeof (char *));
	if (ntab == NULL)
		ft_throw(data, ERR_NULL_CHECK_FAIL, "ft_push ntab", true);
	ntab[size_tab] = NULL;
	while (--size_tab >= 0)
	{
		if (!ft_strncmp(str, (*tab)[--i], ft_strlen(str) + 1))
			i--;
		ntab[size_tab] = ft_strdup ((*tab)[i]);
	}
	ft_destroy_tab(*tab);
	*tab = ntab;
}

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

/*Does not expand environment variables to their values!*/
void	echo(char **args)
{
	int	i;

	i = 0;
	if (*args != NULL && (!ft_strncmp ("-n", *args, 3) || \
		!ft_strncmp ("-", *args, 2)))
		i++;
	while (args[i] != NULL)
	{
		printf("%s", args[i++]);
		if (args[i] != NULL)
			printf(" ");
	}
	if (*args == NULL || ft_strncmp ("-n", *args, 3) != 0)
		printf("\n");
}

void	cd(t_data *data, char *path)
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
			ft_throw (data, ERR_NULL_CHECK_FAIL, "cd cwd", true);
		else if (getcwd(cwd, MAXPATHLEN + 1) == NULL)
		{
			free(cwd);
			ft_throw (data, ERR_NULL_CHECK_FAIL, "cd getcwd", true);
		}
		//free(*env_loc);
		*env_loc = ft_strjoin("PWD=", cwd);
		free(cwd);
	}
}

void	pwd(t_data *data)
{
	char	*cwd;

	cwd = (char *)malloc(MAXPATHLEN + 1);
	if (cwd == NULL)
		ft_throw (data, ERR_NULL_CHECK_FAIL, "pwd cwd", true);
	else if (getcwd(cwd, MAXPATHLEN + 1) == NULL)
	{
		free(cwd);
		ft_throw (data, ERR_NULL_CHECK_FAIL, "pwd getcwd", true);
	}
	printf("%s\n", cwd);		
	free(cwd);
}

void	export(t_data *data, char **args)
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

}

void	unset(t_data *data, char **args)
{
	while (*args != NULL)
		ft_pull(data, &data->envp, *get_env_var(data->envp, *args++));
}

void	env(t_data *data)
{
	int	i;

	i = -1;
	while (data->envp[++i] != NULL)
		printf("%s\n", data->envp[i]);
}

void ft_exit(t_data *data)
{
	ft_destroy_data(data);
	//system("leaks minishell");
	exit (EXIT_SUCCESS);
}

// char	*get_prompt(char **envp)
// {
// 	char	*out;
// 	int		size;
// 	size = ft_strlen(get_env_var(envp, "USER", 1));
// 	size += ft_strlen(get_env_var(envp, "NAME", 1));
// 	size += ft_strlen(get_env_var(envp, "PWD", 1)) + 4;
// 	out = (char *)malloc(size);
// 	ft_strlcat(out, get_env_var(envp, "USER", 1), size);
// 	ft_strlcat(out, "@", size);
// 	ft_strlcat(out, get_env_var(envp, "NAME", 1), size);
// 	ft_strlcat(out, ":", size);
// 	ft_strlcat(out, get_env_var(envp, "PWD", 1), size);
// 	ft_strlcat(out, "$ ", size);
// 	return (out);
// }

int main(int argc, char **argv, char **envp)
{
	t_data *data;
	char buf[200];

	data = ft_initdata(envp);
	if (argc < 1)
		return (1);
	argv++;
	//env test
	if (*argv != NULL && !ft_strncmp ("1", *argv, 2))
		env(data);
	//pwd test
	else if (*argv != NULL && !ft_strncmp ("2", *argv, 2))
		pwd(data);
	//echo test
	else if (*argv != NULL && !ft_strncmp ("3", *argv, 2))
		echo(argv + 1);
	//unset test
	else if (*argv != NULL && !ft_strncmp ("4", *argv, 2))
	{
		env(data);
		unset(data, argv + 1);
		env(data);
	}
	//cd test
	else if (*argv != NULL && !ft_strncmp ("5", *argv, 2))
	{
		printf("%s\n", *get_env_var(envp, "PWD"));
		cd(data, argv[1]);
		printf("%s\n", *get_env_var(envp, "PWD"));
	}
	//export test
	else if (*argv != NULL && !ft_strncmp ("6", *argv, 2))
	{
		env(data);
		export(data, argv + 1);
		env(data);
	}
	ft_destroy_data(data);
}