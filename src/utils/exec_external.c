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

void	exec_external()
{
    char **cmds;
  	char *path;


    cmds = (char**) g_msh.cmds_lst->content; 
  	path = find_cmd_path(*cmds);

    close(g_msh.fd[0]); 
    dup2(g_msh.fd[1], STDOUT_FILENO);
    if(is_builtin(*cmds))
		exec_builtin(cmds);
    else
      execve(path, cmds, g_msh.envp);	
}