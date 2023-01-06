/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 05:43:21 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/06 09:23:55 by katchogl         ###   ########.fr       */
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

static void	ft_catch_cmd_data(t_data *data, int *i, int j)
{
	char	***tab;
	
	ft_assert_not_null (data, data);
	if (ft_strncmp (data->tab[*i], "<", 2) == 0
		|| ft_strncmp (data->tab[*i], ">", 2) == 0
		|| ft_strncmp (data->tab[*i], ">>", 3) == 0
		|| ft_strncmp (data->tab[*i], "<<", 3) == 0)
	{
		if (ft_strncmp (data->tab[*i], "<", 2) != 0)
			tab = &data->cmds[j].infiles;
		else if (ft_strncmp (data->tab[*i], ">", 2) != 0)
			tab = &data->cmds[j].outfiles_trc;
		else if (ft_strncmp (data->tab[*i], "<<",3) != 0)
			tab = &data->cmds[j].heredoc_lims;
		else
			tab = &data->cmds[j].outfiles_app;
		(*i)++;
		if (data->tab[*i] != NULL)
			ft_push (data, tab, data->tab[*i]);
	}
	else if (data->cmds[j].name == NULL)
	{
		data->cmds[j].name = ft_strdup (data->tab[*i]);
		data->cmds[j].pathname = ft_pathname (data, data->cmds[j].name);
	}
	else
		ft_push (data, &data->cmds[j].args, data->tab[*i]);
}

static void ft_parse(t_data *data)
{
	int	i;
	int	j;

	ft_assert_not_null (data, data);
	ft_assert_not_null (data, data->tab);
	i = -1;
	data->cmdsc = 1;
	while (data->tab[++i] != NULL)
		if (ft_strncmp (data->tab[i], "|", 2) == 0)
			data->cmdsc++;
	data->cmds = ft_initcmds (data, data->cmdsc);
	i = 0;
	j = 0;
	while (data->tab[i] != NULL && j < data->cmdsc)
	{
		while (data->tab[i] != NULL && ft_strncmp (data->tab[i], "|", 2) != 0)
		{
			ft_catch_cmd_data (data, &i, j);
			i++;
		}
		if (data->tab[i] != NULL && ft_strncmp (data->tab[i], "|", 2) == 0)
			i++;
		j++;
	}
}

static void	ft_expand(t_data *data)
{
	ft_assert_not_null (data, data);
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
		if (data->line != NULL && ft_strncmp (data->line, "", 1) != 0)
		{
			data->tab = ft_split (data->line, ' ');
			if (ft_isvalid (data))
			{
				ft_expand (data);
				ft_parse (data);
				ft_execute (data);
			}
		}
		ft_destroy_execution (data);
		break ;
	}
	ft_destroy_data (data);
	return (EXIT_SUCCESS);
}
