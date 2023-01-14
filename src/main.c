/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 05:43:21 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/14 14:37:06 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exec(t_data *data)
{
	ft_assert_not_null (data, data);
	data->tab = ft_minishell_split (data, data->line);
	// Debug
	// int i = -1;
	// printf("DEBUG: ");
	// while (data->tab[++i] != NULL)
	// 	printf("'%s' ", data->tab[i]);
	// printf("'%p'\n", data->tab[i]);
	if (ft_isvalid (data) && ft_assert_finished (data))
	{
		data->child_running = true;
		add_history (data->line);
		ft_parse (data);
		ft_heredocs (data);
		ft_execute (data);
		data->child_running = false;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	if (argc != 1 || argv == NULL || envp == NULL)
		return (EXIT_FAILURE);
	data = ft_initdata (envp);
	init_signal_handler(data);
	while (true)
	{
		//Debug
		data->line = readline ("\033[32;1mminishell$ \033[0m");
		if (data->line == NULL)
			ft_exit(data, NULL);
		else if (ft_strncmp (data->line, "", 1) != 0)
			ft_exec (data);
		ft_destroy_execution (data);
	}
	ft_destroy_data (data);
	return (EXIT_SUCCESS);
}
