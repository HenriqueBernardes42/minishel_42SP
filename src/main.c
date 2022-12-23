/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 05:43:21 by katchogl          #+#    #+#             */
/*   Updated: 2022/12/23 20:03:29 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **envp)
{
	t_data	*data;
	char	**tmp_path;
	
	if (argc != 1)
		return (EXIT_FAILURE);
	data = ft_initdata ();
	data->envp = envp;
	ft_setpath (&data);
	while (1)
	{
		data->input = readline ("\033[36;1mminishell >\033[0m");
		if (ft_parse (&data))
			ft_run (data);
		ft_free (&data, FALSE);
	}
	return (EXIT_SUCCESS);
}
