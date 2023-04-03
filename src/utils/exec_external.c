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
    char **cmds;

    cmds = (char**) g_msh.cmds_lst->content; 
    close(g_msh.fd[0]); 
    dup2(g_msh.fd[1], STDOUT_FILENO);
    char *const command[] = {*cmds, NULL};
    if(is_builtin(*cmds))
		exec_builtin(cmds);
    else
        execvp(*cmds, command);
    perror("execvp");
    exit(EXIT_FAILURE);
}
