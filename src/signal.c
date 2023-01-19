/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:34:46 by rburgsta          #+#    #+#             */
/*   Updated: 2023/01/19 14:54:36 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal_handler(int sig, siginfo_t *info, void *ptr)
{
	static t_data *data;

	(void)info;
	if (data == NULL)
		data = (t_data *)ptr;
	if (sig == SIGINT && data->read_state)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		data->status = EXIT_SIGINT;
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_init_signal_handler(t_data *data)
{
	struct sigaction	sa;

	ft_signal_handler(0, NULL, data);
	sa.sa_sigaction = &ft_signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
