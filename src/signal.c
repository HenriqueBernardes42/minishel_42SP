/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:34:46 by rburgsta          #+#    #+#             */
/*   Updated: 2023/01/03 13:22:13 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>

void signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		//write(1, "\nminishell:>", 13);
	}
}

void fputchar(char c)
{
	write(1, &c, 1);
}

int main()
{
	char *input = NULL;

	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, &signal_handler);
	printf("%s\n", getenv("PATH"));
	while (1)
	{
		input = readline("minishell:> ");
		if (input == NULL)
		{
			//printf("%c%cexit\n", 8, 8);
			// fputchar(8);
			// fputchar(8);
			// printf("exit\n");
			system("leaks a.out");
			exit(0);
		}
		add_history(input);
		printf("'%s'\n", input);
		free(input);
	}
}