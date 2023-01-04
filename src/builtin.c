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

char *get_env_var(char **envp, char *var)
{
	int	i;
	int	len;

	len = ft_strlen(var);
	i = -1;
	while (envp[++i] != NULL)
		if (!ft_strncmp(var, envp[i], len) && envp[i][len] == '=')
			return (envp[i]);
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

void	cd(const char *path)
{
	chdir(path);
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
	int		size;
	int		del;
	char	**out;

	size = 0;
	del = 0;
	while (args[size] != NULL)
		if (get_env_var(envp, args[size]) != NULL)
			del++;
	size = 0;
	while (envp[size] != NULL)
		size++;
	out = (char **)malloc((size - del + 1) * sizeof(char *));
	if (!out)
		return (NULL);
	out[size-- - del] == NULL;
	// while (size-- > 0)
	// {
	// 	if ()
	// }
	printf("%i\n", size);
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
	else if (*argv != NULL && !ft_strncmp ("3", *argv, 2))
		echo(argv + 1);
	else if (*argv != NULL && !ft_strncmp ("4", *argv, 2))
		unset(envp, argv + 1);
	else if (*argv != NULL && !ft_strncmp ("ft", *argv, 3))
	{
		getcwd(buf, 200);
		printf("%i %s %i \n%s\n", ttyslot(), ttyname(0), isatty(0), buf);
		chdir("../");
		getcwd(buf, 200);
		printf("%s\n", buf);
	}
	
}