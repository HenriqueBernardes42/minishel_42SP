/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhenriqu <hhenriqu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:36:24 by hhenriqu          #+#    #+#             */
/*   Updated: 2023/03/06 04:22:56 by hhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static	int	ft_str_isdigit(char *str)
{
	int	i;
	int rvalue;

	i = 0;
	if (str[i] != '-' || str[i] != '+')
		++i;
	while (str[i] != '\0')
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == ' ')
{		rvalue = 1;
		i++;}
		else
{		rvalue = 0;
		i++;}
	}
	return(rvalue);
}

void	msh_exit(char **cmd)
{
	write (1, "exit\n", 5);
	if (cmd[1] != NULL && ft_str_isdigit(cmd[1]) == 0)
	{
		g_msh.exit_code = 2;
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	}
	else if (cmd[1] != NULL && cmd[2] != NULL)
	{
		g_msh.exit_code = 1;
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
	}
	else if (cmd[1] != NULL && ft_str_isdigit(cmd[1]) == 1)
		g_msh.exit_code = ft_atol(cmd[1]);
	if (g_msh.exit_code < 0)
		g_msh.exit_code = 156;
	free_all();
	exit(g_msh.exit_code);
}
