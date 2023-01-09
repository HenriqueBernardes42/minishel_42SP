/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 05:43:21 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/09 16:24:20 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Check whether the array of input strings is valid or not.
/// @param data The minishell's data;
/// @return the result.
static bool	ft_isvalid(t_data *data)
{
	int		i;

	ft_assert_not_null (data, data);
	ft_assert_not_null (data, data->tab);
	if (ft_istype (data->tab[0], T_PIPE)
		|| ft_istype (data->tab[0], T_CMD_SEP))
		return (ft_throw (data, ERR_UNEXPECTED_TOKEN, data->tab[0], false));
	i = -1;
	while (data->tab[++i] != NULL)
	{
		if ((ft_istype (data->tab[i], T_SPECIAL)
			&& ft_istype (data->tab[i + 1], T_SPECIAL))
			|| (ft_istype (data->tab[i], T_CMD_SEP) &&
			data->tab[i + 1] != NULL))
			return (ft_throw (data, ERR_UNEXPECTED_TOKEN,
					data->tab[i + 1], false));
		else if ((ft_istype (data->tab[i], T_REDIR) || ft_istype 
			(data->tab[i], T_PIPE)) && data->tab[i + 1] == NULL)
			return (ft_throw (data, ERR_UNEXPECTED_TOKEN,
					"(null)", false));
	}
	return (true);
}

/// @brief Catch or set the members of the current command's struct.
/// @param data The minishell's data;
/// @param i The pointer to the index of the current input string in data->tab;
/// @param j The index of the current command.
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
		data->cmds[j].pathname = ft_pathname (data, data->cmds[j].name);
		ft_push (data, &data->cmds[j].args, data->cmds[j].pathname);
		data->cmds[j].argsc++;
	}
	else
	{
		ft_push (data, &data->cmds[j].args, data->tab[*i]);
		data->cmds[j].argsc++;
	}
}

/// @brief Parse the array of input to an array of structs of type s_cmd.
/// @param data The minishell's data.
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
			if (!ft_istype (data->tab[i], T_CMD_SEP))
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
	init_signal_handler();
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
			add_history (data->line);
		}
		ft_destroy_execution (data);
	}
	ft_destroy_data (data);
	return (EXIT_SUCCESS);
}
