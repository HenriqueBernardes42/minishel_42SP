/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 05:43:21 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/08 12:17:50 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// echo hello world |
// look for bash syntax
bool	ft_isreserved(char *str)
{
	if (ft_strncmp (str, "|", 2) == 0 || ft_strncmp (str, ";", 2) == 0
		|| ft_strncmp (str, ">", 2) == 0 || ft_strncmp (str, ">>", 3) == 0
		|| ft_strncmp (str, "<", 2) == 0 || ft_strncmp (str, "<<", 3) == 0)
		return (true);
	return (false);
}

static bool	ft_isvalid(t_data *data)
{
	int		i;

	ft_assert_not_null (data, data);
	ft_assert_not_null (data, data->tab);
	if (ft_strncmp (data->tab[0], "|", 2) == 0
		|| ft_strncmp (data->tab[0], ";", 2) == 0)
		return (ft_throw (data, ERR_UNEXPECTED_TOKEN, data->tab[0], false));
	i = -1;
	while (data->tab[++i] != NULL)
	{
		if (ft_isreserved (data->tab[i]))
		{
			if (ft_isreserved (data->tab[i + 1]))
				return (ft_throw (data, ERR_UNEXPECTED_TOKEN,
						data->tab[i], false));
		}
	}
	return (true);
}

static void	ft_catch(t_data *data, int *i, int j)
{
	t_redir	redir;

	ft_assert_not_null (data, data);
	redir = ft_getredir (data->tab[*i]);
	if (redir != REDIR_UNDEF)
	{
		ft_addint (data, &data->cmds[j].redirs, data->cmds[j].redirsc, redir);
		data->cmds[j].redirsc++;
		(*i)++;
		if (data->tab[*i] != NULL)
			ft_push (data, &data->cmds[j].args_redir, data->tab[*i]);
	}
	else if (data->cmds[j].name == NULL)
	{
		data->cmds[j].name = ft_strdup (data->tab[*i]);
		if ()
		
		data->cmds[j].pathname = ft_pathname (data, data->cmds[j].name);
		ft_push (data, &data->cmds[j].args, data->cmds[j].pathname);
	}
	else
		ft_push (data, &data->cmds[j].args, data->tab[*i]);
}

static void	ft_parse(t_data *data)
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
			ft_catch (data, &i, j);
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
			data->tab = ft_split (data->line, ' ');
			ft_expand (data);
			if (ft_isvalid (data))
			{
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
