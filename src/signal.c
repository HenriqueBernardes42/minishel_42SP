/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:34:46 by rburgsta          #+#    #+#             */
/*   Updated: 2023/01/21 12:42:22 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_signal_handler_child(int sig)
{
	if (sig == SIGINT)
		exit (2);
	else if (sig == SIGQUIT)
		exit (3);
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

static void	ft_signal_handler_parent_execution(int sig)
{
	if (sig == SIGINT || sig == SIGQUIT)
		ft_putstr_fd ("\n", 2);
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
		signal (SIGINT, ft_signal_handler_parent_execution);
		signal (SIGQUIT, ft_signal_handler_parent_execution);
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
