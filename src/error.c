/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 17:59:43 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/21 12:14:51 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_puterror(t_errno err)
{
	if (err == ERR_DEFAULT)
		ft_putstr_fd ("something went wrong", STDERR_FD);
	else if (err == ERR_NULL_PTR)
		ft_putstr_fd ("null pointer", STDERR_FD);
	else if (err == ERR_FAIL)
		ft_putstr_fd ("fail", STDERR_FD);
	else if (err == ERR_UNEXPECTED_TOKEN)
		ft_putstr_fd ("syntax error near unexpected token", STDERR_FD);
	else if (err == ERR_INVALID_CMDSC)
		ft_putstr_fd ("invalid count of commands", STDERR_FD);
	else if (err == ERR_CMD_NOT_FOUND)
		ft_putstr_fd ("command not found", STDERR_FD);
	else if (err == ERR_ENOENT)
		ft_putstr_fd (strerror (ENOENT), STDERR_FD);
	else if (err == ERR_EACCES)
		ft_putstr_fd (strerror (EACCES), STDERR_FD);
	else if (err == ERR_EISDIR)
		ft_putstr_fd (strerror (EISDIR), STDERR_FD);
	else if (err == ERR_AMBIGUOUS_REDIRECT)
		ft_putstr_fd ("ambiguous redirect", STDERR_FD);
	else if (err == ERR_UNEXPECTED_EOF)
		ft_putstr_fd ("unexpected end of input", STDERR_FD);
	else if (err != 0)
		ft_putstr_fd ("an unexpected error occurred", STDERR_FD);
}

void	ft_putinfo(char *str, char *info, char *str2)
{
	if (info == NULL)
		return ;
	if (str != NULL)
		ft_putstr_fd (str, STDERR_FD);
	ft_putstr_fd (info, STDERR_FD);
	if (str2 != NULL)
		ft_putstr_fd (str2, STDERR_FD);
}

bool	ft_throw(t_data *data, enum e_errno err, char *info, bool exitp)
{
	int	status;

	ft_putstr_fd ("minishell: ", STDERR_FD);
	if (info != NULL && (err == ERR_CMD_NOT_FOUND || err == ERR_EACCES
			|| err == ERR_ENOENT || err == ERR_AMBIGUOUS_REDIRECT))
		ft_putinfo (NULL, info, ": ");
	else if (info != NULL && err == ERR_FAIL)
		ft_putinfo (NULL, info, " ");
	ft_puterror (err);
	if (info != NULL && err == ERR_UNEXPECTED_TOKEN)
		ft_putinfo (" `", info, "'");
	if (info != NULL && err != ERR_UNEXPECTED_TOKEN && err != ERR_ENOENT
		&& err != ERR_CMD_NOT_FOUND && err != ERR_EACCES && err != ERR_FAIL
		&& err != ERR_AMBIGUOUS_REDIRECT)
		ft_putinfo (": `", info, "'");
	ft_putstr_fd ("\n", STDERR_FD);
	if (exitp)
	{
		status = data->status;
		ft_destroy_data (data);
		exit (status);
	}
	return (false);
}
