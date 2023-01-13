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

void	ft_echo(t_data *data, char **args)
{
	int	i;

	i = 0;
	(void)data;
	if (args != NULL && (!ft_strncmp ("-n", *args, 3)
			|| !ft_strncmp ("-", *args, 2)))
		i++;
	while (args != NULL && args[i] != NULL)
	{
		printf("%s", args[i++]);
		if (args[i] != NULL)
			printf(" ");
	}
	if (args == NULL || ft_strncmp ("-n", *args, 3) != 0)
		printf("\n");
	exit (EXIT_SUCCESS);
}

void	ft_pwd(t_data *data)
{
	char	*cwd;

	cwd = (char *)malloc(MAXPATHLEN + 1);
	if (cwd == NULL)
		ft_throw (data, ERR_FAIL, "pwd cwd", true);
	if (getcwd(cwd, MAXPATHLEN + 1) == NULL)
	{
		free(cwd);
		ft_throw (data, ERR_FAIL, "pwd getcwd", true);
	}
	printf("%s\n", cwd);
	free(cwd);
	exit (EXIT_SUCCESS);
}

static int	valid_number(t_data *data, char *str)
{
	int	i;

	i = 0;
	ft_assert_not_null(data, str);
	while (str[i] != '\0' && (str[i] == 32 || (str[i] < 14 && str[i] > 8)))
		i++;
	if (str[i] == '\0')
		return (false);
	if (str[i] == '-')
		i++;
	while (str[i] != '\0' && str[i] <= '9' && str[i] >= '0')
		i++;
	while (str[i] != '\0' && (str[i] == 32 || (str[i] < 13 && str[i] > 8)))
		i++;
	if (str[i] != '\0')
		return (false);
	return (true);
}

void	ft_exit(t_data *data, char **args)
{
	int	i;

	printf("exit\n");
	if (args == NULL)
		ft_destroy_data(data);
	else
	{
		if (!valid_number(data, *args))
		{
			printf("bash: exit: %s: numeric argument required\n", *args);
			ft_destroy_data(data);
			exit(2);
		}
		else if (*(args + 1) != NULL)
		{
			data->ret_pipe = EXIT_FAILURE;
			printf("bash: exit: too many arguments\n");
			return ;
		}
		i = ft_atoi(*args);
		ft_destroy_data(data);
		exit(i);
	}
	exit (EXIT_SUCCESS);
}

void	ft_env(t_data *data)
{
	int	i;

	i = -1;
	ft_assert_not_null (data, data->envp);
	while (data->envp[++i] != NULL)
		printf("%s\n", data->envp[i]);
	exit (EXIT_SUCCESS);
}
