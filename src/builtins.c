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
	while (args != NULL && args[i] && !ft_strncmp ("-n", args[i], 3))
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
	ft_assert_not_null(data, cwd);
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

	i = data->status;
	ft_putstr_fd ("exit\n", STDERR_FD);
	if (args != NULL)
	{
		if (!valid_number(data, *args))
		{
			ft_putinfo ("minishell: exit: ", *args,
				": numeric argument required\n");
			i = 2;
		}
		else if (*(args + 1) != NULL)
		{
			data->status = EXIT_FAILURE;
			ft_putstr_fd ("minishell: exit: too many arguments\n", STDERR_FD);
			return ;
		}
		else
			i = ft_atoi (*args);
	}
	ft_destroy_data (data);
	exit (i);
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
