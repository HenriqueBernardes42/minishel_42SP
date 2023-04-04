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

static void	parent_command(pid_t pid1, pid_t pid2)
{
	int status;
	pid2 = fork();

	dprintf(2,"dasd\n");
    if (pid2 == -1)
	{
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0)
	{
        // Child process 2
		char **cmds;

    	cmds = (char**) g_msh.cmds_lst->next->content; 
		dprintf(2,"child2 = %s\n", *cmds);
        close(g_msh.fd[1]);

        dup2(g_msh.fd[0], STDIN_FILENO); 

        char *const cmd[] = {*cmds, NULL};
		if(is_builtin(*cmds))
			exec_builtin(cmds);
        else
			execvp(*cmds, cmd);
        perror("execvp");
        exit(EXIT_FAILURE);
    } 
	else 
	{
    // Parent process
    close(g_msh.fd[0]); // Close unused read end
    close(g_msh.fd[1]); // Close unused write end

	if(pid1 != 100)
    	waitpid(pid1, &status, 0); // Wait for child process 1 to exit
    // if (WIFEXITED(status)) {
    //     printf("Child process 1 exited with status %d\n", WEXITSTATUS(status));
    // } else if (WIFSIGNALED(status)) {
    //     printf("Child process 1 terminated by signal %d\n", WTERMSIG(status));
    // } else if (WIFSTOPPED(status)) {
    //     printf("Child process 1 stopped by signal %d\n", WSTOPSIG(status));
    // }

    waitpid(pid2, &status, 0); // Wait for child process 2 to exit
    // if (WIFEXITED(status))
	// {
    // 	    printf("Child process 2 exited with status %d\n", WEXITSTATUS(status));
    // 	} else if (WIFSIGNALED(status)) {
    // 	    printf("Child process 2 terminated by signal %d\n", WTERMSIG(status));
    // 	} else if (WIFSTOPPED(status)) {
    // 	    printf("Child process 2 stopped by signal %d\n", WSTOPSIG(status));
    // }
            
    // exit(EXIT_SUCCESS);
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
    pid_t pid1, pid2;
	// char **cmds;
	// cmds = (char**) g_msh.cmds_lst->content; 

	pid1 = 0;
	pid2 = 0;

	// dprintf(2,"built_in = %d\n", is_builtin(*cmds));
	// dprintf(2,"n_commands = %d\n", g_msh.nmbr_of_commands);

	signal(SIGQUIT, handle_quit);
	if (pipe(g_msh.fd) == -1)
		exit (-1);
	else
	{
		// dprintf(2,"nmbr = %d\n", g_msh.nmbr_of_pipes);
		if(g_msh.nmbr_of_pipes < 2)
			just_one(pid1);
		else
		{
			pid1 = fork();
			if (pid1 == 0)
				exec_external();
			else
				parent_command(pid1, pid2);
		}
	}
	dup2(g_msh.fd[0], STDIN_FILENO);
	dup2(g_msh.save_stdout, STDOUT_FILENO);
	close(g_msh.fd[0]);
	close(g_msh.fd[1]);
}
