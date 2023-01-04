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


/*Does not expand environment variables to their values!*/
void echo(char **args)
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

// void cd(char **envp, char *path)
// {
	
// }

void pwd(char **envp)
{
	while (*envp != NULL && ft_strncmp ("PWD=", *envp, 4))
		envp++;
	if (*envp != NULL)
		printf("%s\n", *envp + 4);
}

void unset(char **envp)
{
	
}

void env(char **envp)
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
}