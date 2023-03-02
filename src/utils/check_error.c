/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhenriqu <hhenriqu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:32:57 by hhenriqu          #+#    #+#             */
/*   Updated: 2023/02/19 20:16:50 by hhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	check_syntax_error(char c)
{
	if (c == '|' || c == '&' || c == ';' || c == '(' \
	|| c == ')' || c == '<' || c == '>' || c == '\0')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (c == '\0')
			ft_putstr_fd("newline", 2);
		else
			ft_putchar_fd(c, 2);
		ft_putstr_fd("'\n", 2);
		g_msh.error = 1;
		g_msh.exit_code = 2;
		return (1);
	}
	return (0);
}

int	check_dir(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

void	check_directory_error(char *file)
{
	if (file == NULL)
		return ;
	if (check_dir(file) == 1 && g_msh.error == 0)
	{
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		g_msh.error = 1;
		g_msh.exit_code = 1;
	}
}
