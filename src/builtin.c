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
#include "../libft/libft.h"
#include <unistd.h>
#include <sys/stat.h>

static char **get_env_var(char **envp, char *var)
{
	int	i;
	int	len;

	len = ft_strlen(var);
	i = -1;
	while (envp[++i] != NULL)
		if (!ft_strncmp(var, envp[i], len) && envp[i][len] == '=')
			return (envp + i);
	return (NULL);
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

int	directory_exists(const char *path)
{
    struct stat	stats;

    stat(path, &stats);
    if (S_ISDIR(stats.st_mode))
        return (1);
    return (0);
}

void	cd(char **envp, char *path)
{
	char	*pwd;
	char	**env_loc;

	env_loc = get_env_var(envp, "PWD");
	if (ft_strchr(*env_loc, '.') == NULL)
	{
		if (directory_exists(path))
			*env_loc = ft_strjoin("PWD=", path);
		else
			printf("cd: no such file or directory: %s\n", path);
	}
}

void	pwd(char **envp)
{
	while (*envp != NULL && ft_strncmp ("PWD=", *envp, 4))
		envp++;
	if (*envp != NULL)
		printf("%s\n", *envp + 4);
}

void	export(char **envp)
{
	
}

char	**unset(char **envp, char **args)
{
	char **out;
	int	del;
	int i;
	int i2;

	del = 0;
	i = 0;
	while (args[i] != NULL)
		if (get_env_var(envp, args[i++]) != NULL)
			del++;
	i = 0;
	while (envp[i] != NULL)
		i++;
	out = (char **)malloc(i - del + 1);
	if (out != NULL)
	{
		out[i - del] = NULL;
		while (--i >= 0)
		{
			i2 = -1;
			while (args[++i2] != NULL)
			{
				if (!ft_strncmp(args[i2], envp[i], ft_strlen(args[i2])) && envp[i][ft_strlen(args[i2])] == '=')
				{
					i--;
					del--;
				}
			}
			out[i - del] = envp[i];
		}
	}
	return (out);
}

void	env(char **envp)
{
	while (*envp != NULL)
		printf("%s\n", *envp++);
}

// void exit()
// {
// 	ft_destroy_data (data);
// 	system ("leaks minishell");
// 	exit (EXIT_SUCCESS);
// }

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
	char buf[200];
	if (argc < 1)
		return (1);
	argv++;
	//env test
	if (*argv != NULL && !ft_strncmp ("1", *argv, 2))
		env(envp);
	//pwd test
	else if (*argv != NULL && !ft_strncmp ("2", *argv, 2))
		pwd(envp);
	//echo test
	else if (*argv != NULL && !ft_strncmp ("3", *argv, 2))
		echo(argv + 1);
	//unset test
	else if (*argv != NULL && !ft_strncmp ("4", *argv, 2))
	{
		env(envp);
		env(unset(envp, argv + 1));
	}
	//cd test
	else if (*argv != NULL && !ft_strncmp ("5", *argv, 2))
	{
		printf("%s\n", *get_env_var(envp, "PWD"));
		cd(envp, argv[1]);
		printf("%s\n", *get_env_var(envp, "PWD"));
	}
	else if (*argv != NULL && !ft_strncmp ("ft", *argv, 3))
	{
		getcwd(buf, 200);
		printf("%i %s %i \n%s\n", ttyslot(), ttyname(0), isatty(0), buf);
		chdir("../");
		getcwd(buf, 200);
		printf("%s\n", buf);
	}
	
}