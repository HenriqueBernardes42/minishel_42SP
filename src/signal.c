/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:34:46 by rburgsta          #+#    #+#             */
/*   Updated: 2023/01/10 10:25:40 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(0, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		write(1, "\033[32;1mminishell$ \033[0m", 23);
}

void	init_signal_handler(void)
{
	struct sigaction	sa;

	sa.sa_handler = &signal_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	printf("PID: %i\n", getpid());
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

// int main()
// {
// 	char *input = NULL;

// 	struct sigaction	sa;

// 	sa.sa_handler = &signal_handler;
// 	sa.sa_flags = SA_RESTART;
// 	sigemptyset(&sa.sa_mask);
// 	printf("PID: %i\n", getpid());
// 	sigaction(SIGINT, &sa, NULL);
// 	sigaction(SIGQUIT, &sa, NULL);
// 	while (1)
// 	{
// 		input = readline("\033[36;1mminishell >\033[0m");
// 		if (input == NULL)
// 		{
// 			//printf("%c%cexit\n", 8, 8);
// 			printf("exit\n");
// 			exit(0);
// 		}
// 		else if (input[0] != '\0')
// 			add_history(input);
// 		printf("'%s'\n", input);
// 		free(input);
// 	}
// }
