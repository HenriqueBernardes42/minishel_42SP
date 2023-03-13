/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhenriqu <hhenriqu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:34:33 by hhenriqu          #+#    #+#             */
/*   Updated: 2023/03/13 18:44:33 by hhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	signal_handler(int signum)
{
	(void)signum;
	if (g_msh.here_doc == 1)
	{
		close (STDIN_FILENO);
		g_msh.error = 1;
		write (1, "\n", 1);
	}
	else if (g_msh.pid != 0)
	{
		kill(g_msh.pid, SIGKILL);
		write (1, "\n", 1);
	}
	else
	{
		write (1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_msh.exit_quit = 130;
}

void	signal_exit(int signum)
{
	write (1, "\n", 1);
	free_all();
	exit(signum);
}

void	handle_quit(void)
{
	signal(SIGQUIT, SIG_IGN);
	printf("Quit (core dumped)\n");
	g_msh.exit_quit = 131;
}
