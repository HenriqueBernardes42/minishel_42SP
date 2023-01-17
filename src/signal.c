/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:34:46 by rburgsta          #+#    #+#             */
/*   Updated: 2023/01/17 15:08:50 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal_handler(int sig, siginfo_t *info, void *ptr)
{
	static t_data *data;

	(void)info;
	if (data == NULL)
		data = (t_data *)ptr;
	if (sig == SIGINT)
		write(1, "\n", 1);
	if (sig == SIGINT)
	{
		if (data->read_state)
		{
			rl_replace_line ("", 0);
			rl_forced_update_display ();
		}
		data->status = EXIT_FAILURE;
	}
	else if (sig == SIGQUIT)
	{
		ft_putendl_fd ("received SIGQUIT", 2);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		write(1, "\n", 1);
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
