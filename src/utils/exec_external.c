/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhenriqu <hhenriqu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:33:30 by hhenriqu          #+#    #+#             */
/*   Updated: 2023/02/17 14:33:31 by hhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	exec_external()
{
	// char	*path;
	// char *const comando[] = {"cat", NULL};
	// dprintf(2,"cmd == %s\n", cmd);

    // Child process 1
    close(g_msh.fd[0]); // Close unused read end

    dup2(g_msh.fd[1], STDOUT_FILENO); // Redirect stdout to write end of pipe

    char *const command[] = {"cat", NULL};
    execvp("cat", command);
    perror("execvp"); // execvp only returns on error
    exit(EXIT_FAILURE);
}
