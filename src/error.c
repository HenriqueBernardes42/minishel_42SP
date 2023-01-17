/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 17:59:43 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/17 17:49:35 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_error(t_errno err)
{
	if (err == ERR_DEFAULT)
		printf ("something went wrong");
	else if (err == ERR_NULL_PTR)
		printf ("null pointer");
	else if (err == ERR_FAIL)
		printf ("fail");
	else if (err == ERR_UNEXPECTED_TOKEN)
		printf ("syntax error near unexpected token");
	else if (err == ERR_INVALID_CMDSC)
		printf ("invalid count of commands");
	else if (err == ERR_CMD_NOT_FOUND)
		printf ("command not found");
	else if (err == ERR_ENOENT)
		printf ("%s", strerror (ENOENT));
	else if (err == ERR_EACCES)
		printf ("%s", strerror (EACCES));
	else if (err == ERR_EISDIR)
		printf ("%s", strerror (EISDIR));
	else if (err == ERR_AMBIGUOUS_REDIRECT)
		printf ("ambiguous redirect");
	else if (err == ERR_UNEXPECTED_EOF)
		printf ("unexpected end of input");
	else if (err != 0)
		printf ("an unexpected error occurred");
}

static void	ft_pexit(enum e_errno err)
{
	int	exit_code;

	exit_code = EXIT_FAILURE;
	if (err == ERR_CMD_NOT_FOUND)
		exit_code = EXIT_CMDNOTFOUND;
	exit (exit_code);
}

bool	ft_throw(t_data *data, enum e_errno err, char *info, bool exitp)
{
	printf ("minishell: ");
	if (info != NULL && (err == ERR_CMD_NOT_FOUND || err == ERR_EACCES
			|| err == ERR_ENOENT || err == ERR_AMBIGUOUS_REDIRECT))
		printf ("%s: ", info);
	else if (info != NULL && err == ERR_FAIL)
		printf ("%s ", info);
	ft_error (err);
	if (info != NULL && err == ERR_UNEXPECTED_TOKEN)
		printf (" `%s'", info);
	if (info != NULL && err != ERR_UNEXPECTED_TOKEN && err != ERR_ENOENT
		&& err != ERR_CMD_NOT_FOUND && err != ERR_EACCES && err != ERR_FAIL
		&& err != ERR_AMBIGUOUS_REDIRECT)
		printf (": `%s'", info);
	printf ("\n");
	if (exitp)
	{
		ft_destroy_data (data);
		ft_pexit (err);
	}
	return (false);
}
