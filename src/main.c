/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 05:43:21 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/12 12:34:09 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	if (argc != 1 || argv == NULL || envp == NULL)
		return (EXIT_FAILURE);
	data = ft_initdata (envp);
	while (true)
	{
		data->line = readline ("\033[32;1mminishell$ \033[0m");
		if (data->line != NULL && ft_strncmp (data->line, "", 1) != 0)
		{
			data->tab = ft_minishell_split (data, data->line);
			if (ft_isvalid (data) && ft_assert_finished (data))
			{
				add_history (data->line);
				ft_parse (data);
				ft_heredocs (data);
				ft_execute (data);
			}
		}
		ft_destroy_execution (data);
	}
	ft_destroy_data (data);
	return (EXIT_SUCCESS);
}
