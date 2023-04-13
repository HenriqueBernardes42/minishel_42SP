/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhenriqu <hhenriqu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 02:42:07 by hhenriqu          #+#    #+#             */
/*   Updated: 2023/04/13 02:21:06 by hhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_signal_handler_child(int sig)
{
	if (sig == SIGINT)
		exit (EXIT_SIGINT_CHILD);
	else if (sig == SIGQUIT)
		exit (EXIT_SIGQUIT_CHILD);
}

static void	ft_signal_handler_parent(int sig)
{
	if (sig == SIGINT)
	{
		if (g_heredoc_success)
			write (1, "\n", 1);
		rl_on_new_line ();
		rl_replace_line ("", 0);
		rl_redisplay ();
	}
}

static void	ft_signal_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_heredoc_success = false;
		close (STDIN_FILENO);
	}
}

void	ft_signals(t_signals signals)
{
	if (signals == SIG_PARENT)
	{
		signal (SIGINT, ft_signal_handler_parent);
		signal (SIGQUIT, SIG_IGN);
	}
	else if (signals == SIG_PARENT_EXECUTION)
	{
		signal (SIGINT, SIG_IGN);
		signal (SIGQUIT, SIG_IGN);
	}
	else if (signals == SIG_HEREDOC)
	{
		signal (SIGINT, ft_signal_handler_heredoc);
		signal (SIGQUIT, SIG_IGN);
	}
	else if (signals == SIG_CHILD)
	{
		signal (SIGINT, ft_signal_handler_child);
		signal (SIGQUIT, ft_signal_handler_child);
	}
}
