/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:34:46 by rburgsta          #+#    #+#             */
/*   Updated: 2023/01/14 13:37:16 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig, siginfo_t *info, void *ptr)
{
	static t_data *data;

	(void)info;
	if (data == NULL)
		data = (t_data *)ptr;
	if (sig == SIGINT)
		write(1, "\n", 1);
	if (sig == SIGINT && data->child_running == false)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		data->ret_pipe = EXIT_FAILURE;
	}
	else if (sig == SIGQUIT &&data->child_running == false)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		write(1, "\n", 1);
}

void	init_signal_handler(t_data *data)
{
	struct sigaction	sa;

	signal_handler(0, NULL, data);
	sa.sa_sigaction = &signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
