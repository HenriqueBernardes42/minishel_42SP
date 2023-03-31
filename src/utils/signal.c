/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhenriqu <hhenriqu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:34:33 by hhenriqu          #+#    #+#             */
/*   Updated: 2023/02/26 20:04:41 by hhenriqu         ###   ########.fr       */
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
	else
	{
		write (1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_msh.exit_code = 130;
}

void	signal_exit(int signum)
{
	write (1, "\n", 1);
	free_all();
	exit(signum);
}

void handle_quit()
{
	signal(SIGQUIT, SIG_IGN);
	printf("Quit (core dumped)\n");
}


