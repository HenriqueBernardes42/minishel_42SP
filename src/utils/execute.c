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

    if (pid2 == -1)
	{
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0)
	{
        // Child process 2
        close(g_msh.fd[1]); // Close unused write end

        dup2(g_msh.fd[0], STDIN_FILENO); // Redirect stdin to read end of pipe

        char *const cmd[] = {"ls", NULL};
        execvp("ls", cmd);
        perror("execvp"); // execvp only returns on error
        exit(EXIT_FAILURE);
    } 
	else 
	{
    // Parent process
    close(g_msh.fd[0]); // Close unused read end
    close(g_msh.fd[1]); // Close unused write end

    waitpid(pid1, &status, 0); // Wait for child process 1 to exit
    if (WIFEXITED(status)) {
        printf("Child process 1 exited with status %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("Child process 1 terminated by signal %d\n", WTERMSIG(status));
    } else if (WIFSTOPPED(status)) {
        printf("Child process 1 stopped by signal %d\n", WSTOPSIG(status));
    }

    waitpid(pid2, &status, 0); // Wait for child process 2 to exit
    if (WIFEXITED(status))
	{
    	    printf("Child process 2 exited with status %d\n", WEXITSTATUS(status));
    	} else if (WIFSIGNALED(status)) {
    	    printf("Child process 2 terminated by signal %d\n", WTERMSIG(status));
    	} else if (WIFSTOPPED(status)) {
    	    printf("Child process 2 stopped by signal %d\n", WSTOPSIG(status));
    }
            
    // exit(EXIT_SUCCESS);
    }
}

void	execute(char **cmd)
{
    pid_t pid1, pid2;

	pid1 = 0;
	pid2 = 0;

	dprintf(2,"cmds = %s\n", (char*) cmd);
	signal(SIGQUIT, handle_quit);
	if (pipe(g_msh.fd) == -1)
		exit (-1);
	// if (g_msh.last_cmd == 0)
	// 	dup2(g_msh.fd[1], STDOUT_FILENO);
	// else if (g_msh.file_name && g_msh.last_cmd == 1 && g_msh.redirect == '>')
	// {
	// 	dup2(g_msh.fdout, STDOUT_FILENO);
	// 	close(g_msh.fdout);
	// }
	// if (is_builtin(*cmd)) <<<<<----- remanejar
	// 	exec_builtin(cmd);
	else
	{
		pid1 = fork();
		if (pid1 == 0)
		{
			// dprintf(2,"child == %s\n", (char*) g_msh.cmds_lst->content);
			exec_external();
		}
		else
		{
			// int status;
			//  waitpid(g_msh.pid, &status, 0);
			// dprintf(2,"parent cmd == %d\n", *cmd[1]);
			parent_command(pid1, pid2);
		}
	}
	dup2(g_msh.fd[0], STDIN_FILENO);
	dup2(g_msh.save_stdout, STDOUT_FILENO);
	close(g_msh.fd[0]);
	close(g_msh.fd[1]);
}
