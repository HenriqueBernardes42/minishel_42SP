/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 11:33:16 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/08 11:33:16 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Does not expand environment variables to their values!*/
void	ft_echo(char **args)
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
	exit (EXIT_SUCCESS);
}

void	ft_pwd(t_data *data) // ok
{
	char	*cwd;

	cwd = (char *)malloc(MAXPATHLEN + 1);
	if (cwd == NULL)
		ft_throw (data, ERR_FAIL, "pwd cwd", true);
	else if (getcwd(cwd, MAXPATHLEN + 1) == NULL)
	{
		free(cwd);
		ft_throw (data, ERR_FAIL, "pwd getcwd", true);
	}
	printf("%s\n", cwd);
	free(cwd);
	exit (EXIT_SUCCESS);
}

void ft_exit(t_data *data)
{
	ft_destroy_data(data);
	exit (EXIT_SUCCESS);
}

void	ft_env(t_data *data)
{
	int	i;

	i = -1;
	while (data->envp[++i] != NULL)
		printf("%s\n", data->envp[i]);
	exit (EXIT_SUCCESS);
}
