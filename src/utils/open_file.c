/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhenriqu <hhenriqu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:34:04 by hhenriqu          #+#    #+#             */
/*   Updated: 2023/02/17 14:34:05 by hhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	open_delimiter(void)
{
	int		fd;
	char	*line;

	if (access(".here_doc", F_OK))
		unlink(".here_doc");
	fd = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL || ft_strcmp(line, g_msh.file_name) == 1)
		{
			if (line != NULL)
				free (line);
			if (line == NULL && g_msh.error == 0)
				ft_printf("warning: here-document delimited by"
					" end-of-file (wanted `%s')\n", g_msh.file_name);
			close(fd);
			g_msh.fdin = open(".here_doc", O_RDONLY);
			unlink(".here_doc");
			return ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

void	open_file_input(void)
{
	if (g_msh.doble_redirect == 1)
	{
		g_msh.here_doc = 1;
		open_delimiter();
		g_msh.here_doc = 0;
	}
	else
	{
		if (access(g_msh.file_name, F_OK | R_OK) == -1)
		{
			write (2, g_msh.file_name, ft_strlen(g_msh.file_name));
			write (2, ": No such file or directory\n", 28);
			g_msh.error = 1;
			g_msh.exit_code = 1;
			return ;
		}
		else
			g_msh.fdin = open(g_msh.file_name, O_RDONLY);
	}
	dup2(g_msh.fdin, STDIN_FILENO);
	close(g_msh.fdin);
}

void	open_file_output(void)
{
	if (g_msh.doble_redirect == 1)
	{
		if (access(g_msh.file_name, F_OK) == -1)
			g_msh.fdout = open(g_msh.file_name, O_CREAT | O_WRONLY | O_APPEND);
		else
			g_msh.fdout = open(g_msh.file_name, O_WRONLY | O_APPEND);
	}
	else
	{
		if (access(g_msh.file_name, F_OK) == -1)
			g_msh.fdout = open(g_msh.file_name, O_CREAT | O_WRONLY );
		else if (access(g_msh.file_name, W_OK) == -1)
		{
			printf("bash: %s\n", strerror(EACCES));
			g_msh.fdout = -1;
		}
		else
			g_msh.fdout = open(g_msh.file_name, O_WRONLY | O_TRUNC );
	}
}
