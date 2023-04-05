/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhenriqu <hhenriqu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:33:45 by hhenriqu          #+#    #+#             */
/*   Updated: 2023/03/13 18:40:47 by hhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static void	parent_command(pid_t *pids)
{
	int status;
	pids[1] = fork();

    if (pids[1] == -1)
	{
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pids[1] == 0)
	{
        // Child process 2
		char **cmds;
		char *path;

    	cmds = (char**) g_msh.cmds_lst->next->content; 
		path = find_cmd_path(*cmds);
        close(g_msh.fd[1]);
        dup2(g_msh.fd[0], STDIN_FILENO); 
		if(is_builtin(*cmds))
			exec_builtin(cmds);
        else
			execve(path, cmds, g_msh.envp);	
    } 
	else 
	{
    // Parent process
    close(g_msh.fd[0]);
    close(g_msh.fd[1]);

	waitpid(pids[0], &status, 0);
    waitpid(pids[1], &status, 0);
    }
}

void just_one()
{
	char **cmds;
	char *path;

    cmds = (char**) g_msh.cmds_lst->content;
	path = find_cmd_path(*cmds);
    if(is_builtin(*cmds))
		exec_builtin(cmds);
    else
        execve(path, cmds, g_msh.envp);	
}

void	execute()
{
    pid_t *pids;

	signal(SIGQUIT, handle_quit);
	if (pipe(g_msh.fd) == -1)
		exit (-1);
	else
	{
		if(g_msh.nmbr_of_pipes == 1)
			just_one();
		else
		{
			pids = ft_calloc(g_msh.nmbr_of_pipes - 1, sizeof(pid_t));
			pids[0] = fork();
			if (pids[0] == 0)
				exec_external();
			else
				parent_command(pids);
		}
	}
	dup2(g_msh.fd[0], STDIN_FILENO);
	dup2(g_msh.save_stdout, STDOUT_FILENO);
	close(g_msh.fd[0]);
	close(g_msh.fd[1]);
}
