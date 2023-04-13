/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhenriqu <hhenriqu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 02:42:07 by hhenriqu          #+#    #+#             */
/*   Updated: 2023/04/13 02:38:24 by hhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quit(int sig)
{
	if (sig)
	{
		signal (SIGQUIT, SIG_IGN);
		printf("Quit (core dumped)\n");
	}
}

void	handle_int(int sig)
{
	if (sig)
	{
		signal (SIGQUIT, handle_quit);
		printf("\n");
	}
}
