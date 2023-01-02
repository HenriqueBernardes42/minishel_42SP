/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 05:43:21 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/02 19:15:56 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **envp)
{
	t_data	*data;
	
	if (argc != 1)
		return (EXIT_FAILURE);
	data = ft_initdata ();
	data->envp = envp;
	ft_setpath (data);
	while (true)
	{
		data->input = readline ("\033[32;1mminishell >\033[0m");
		if (data->input != NULL && ft_strncmp (data->input, "", 2) != 0)
		{
			if (ft_parse (data))
				ft_exec (data);
			ft_free (data, false);
		}
	}
	ft_free (data, true);
	return (EXIT_SUCCESS);
}
