/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 05:43:21 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/03 20:20:39 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_isvalid(t_data *data)
{
	int	i;

	ft_assert_not_null (data, data);
	ft_assert_not_null (data, data->tab);
	i = -1;
	while (data->tab[++i] != NULL)
	{
		if ((i == 0 && ft_strncmp (data->tab[i], "|", 2) == 0)
			|| (ft_strncmp (data->tab[i], "|", 2) == 0
				&& ft_strncmp (data->tab[i + 1], "|", 2) == 0))
			return (ft_throw (data, ERR_UNEXPECTED_TOKEN,
				data->tab[i], false));
	}
	return (true);
}

static void ft_parse(t_data *data)
{
	int	pipesc;
	int	i;
	int	j;
	int	c;

	ft_assert_not_null (data, data);
	ft_assert_not_null (data, data->tab);
	i = -1;
	pipesc = 0;
	while (data->tab[++i] != NULL)
		if (ft_strncmp (data->tab[i], "|", 2) == 0)
			pipesc++;
	data->cmds = (char ***) malloc ((pipesc + 2) * sizeof (char **));
	data->cmds[pipesc + 1] = NULL;
	i = -1;
	j = -1;
	while (++j < pipesc + 1)
	{
		c = 0;
		while (data->tab[++i] != NULL && ft_strncmp (data->tab[i], "|", 2) != 0)
			c++;
		data->cmds[j] = (char **) malloc ((c + 1) * sizeof (char *));
		i -= c + 1;
		c = -1;
		while (data->tab[++i] != NULL && ft_strncmp (data->tab[i], "|", 2) != 0)
			data->cmds[j][++c] = data->tab[i];
	}
}

int main(int argc, char **envp)
{
	t_data	*data;
	
	if (argc != 1)
		return (EXIT_FAILURE);
	data = ft_initdata (envp);
	while (true) 
	{
		data->line = readline ("\033[32;1mminishell$ \033[0m");
		if (data->line != NULL && ft_strncmp (data->line, "", 2) != 0)
		{
			data->tab = ft_split (data->line, ' ');
			if (ft_isvalid (data))
			{
				ft_expand (data);
				ft_parse (data);
				ft_execute (data);
			}
		}
		ft_freeinput (data);
	}
	ft_freedata (data);
	system ("leaks minishell");
	return (EXIT_SUCCESS);
}
