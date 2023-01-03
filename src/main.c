/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 05:43:21 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/03 14:52:47 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_data 	*ft_initdata(void)
{
	t_data	*data;

	data = (t_data *) malloc (sizeof (t_data));
	ft_assert_not_null (data, data);
	data->envp = NULL;
	data->path = NULL;
	data->input = NULL;
	data->line = NULL;
	return (data);
}

static bool	ft_isvalid(t_data *data)
{
	int	i;

	ft_assert_not_null (data, data);
	ft_assert_not_null (data, data->input);
	i = -1;
	while (data->input[++i] != NULL)
	{
		if (i == 0 && ft_strncmp (data->input[i], "|", 2) == 0)
			return (ft_throw (data, ERR_UNEXPECTED_TOKEN,
				data->input[i], false));
	}
	return (true);
}

int main(int argc, char **envp)
{
	t_data	*data;
	
	if (argc != 1)
		return (EXIT_FAILURE);
	data = ft_initdata ();
	data->envp = envp;
	data->path = ft_split (getenv (PATH), ':');
	while (true)
	{
		data->line = readline ("\033[32;1mminishell$ \033[0m");
		if (data->line != NULL && ft_strncmp (data->line, "", 2) != 0)
		{
			data->input = ft_split (data->line, ' ');
			if (ft_isvalid (data))
			{
				// execute
			}
		}
		ft_freeinput (data);
	}
	ft_freedata (data);
	return (EXIT_SUCCESS);
}
