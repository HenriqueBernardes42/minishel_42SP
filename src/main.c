/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 05:43:21 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/11 18:51:03 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_isvalid (t_data *data)
{
	int	i;
	int opened;
	
	ft_assert_not_null (data, data);
	ft_assert_not_null (data, data->tab);
	i = -1;
	opened = 0;
	while (data->tab[++i] != NULL)
	{
		if (ft_istype (data->tab[i], T_REDIR, true))
		{
			if (data->tab[i + 1] == NULL)
				return (ft_throw (data, ERR_UNEXPECTED_TOKEN,
					"(null)", false));
			else if (ft_istype (data->tab[i + 1], T_SPECIAL, true))
				return (ft_throw (data, ERR_UNEXPECTED_TOKEN,
					data->tab[i + 1], false));
		}
		else if (ft_istype (data->tab[i], T_PARENTH_OPEN, true))
		{
			opened++;
			// if (open)
			// 	return (ft_throw (data, ERR_UNEXPECTED_TOKEN,
			// 		data->tab[i], false));
			// else if (i != 0 && !ft_istype (data->tab[i - 1], T_CMD_CAT, true))
			// 	return (ft_throw (data, ERR_UNEXPECTED_TOKEN,
			// 		data->tab[i], false));
			// else
		}
		else if(ft_istype (data->tab[i], T_PARENTH_CLOSE, true))
		{
			if (opened <= 0 || ft_istype (data->tab[i - 1], T_PIPE, true))
				return (ft_throw (data, ERR_UNEXPECTED_TOKEN,
					data->tab[i], false));
			else
				opened--;
		}
		else if (ft_istype (data->tab[i], T_CMD_SEP, true)
			&& opened > 0)
			return (ft_throw (data, ERR_UNEXPECTED_TOKEN,
				data->tab[i], false));
		else if (ft_istype (data->tab[i], T_CMD_CAT, true) 
			&& (i == 0 || ft_istype (data->tab[i - 1], T_CMD_CAT, true)))
			return (ft_throw (data, ERR_UNEXPECTED_TOKEN,
				data->tab[i], false));
		else if (ft_istype (data->tab[i], T_CMD_SEP, true)
			&& data->tab[i + 1] != NULL)
			return (ft_throw (data, ERR_UNEXPECTED_TOKEN,
				data->tab[i + 1], false));
		else if (ft_strncmp (data->tab[i], "\\", 2) == 0)
			return (ft_throw (data, ERR_UNEXPECTED_TOKEN,
				data->tab[i], false));
	}
	if (opened > 0)
		return (ft_throw (data, ERR_UNEXPECTED_TOKEN,
			"(null)", false));
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
		if (!ft_isbuiltin (data->cmds[j].name))
		{
			data->cmds[j].pathname = ft_pathname (data, data->cmds[j].name);
			ft_push (data, &data->cmds[j].args, data->cmds[j].pathname);
			data->cmds[j].argsc++;
		}
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
	int	lvl;
	int	inst;

	ft_assert_not_null (data, data);
	ft_assert_not_null (data, data->tab);
	data->cmdsc = 1;
	i = -1;
	while (data->tab[++i] != NULL)
		if (ft_istype (data->tab[i], T_PIPE, true)
			|| ft_istype (data->tab[i], T_OP, true))
			data->cmdsc++;
	data->cmds = ft_initcmds (data, data->cmdsc);
	i = 0;
	j = 0;
	lvl = 0;
	inst = I_START;
	while (data->tab[i] != NULL && j < data->cmdsc)
	{
		if (ft_istype (data->tab[i], T_SPECIAL, true))
		{
			if (ft_istype (data->tab[i], T_PARENTH_OPEN, true))
				lvl++;
			else if (ft_istype (data->tab[i], T_PARENTH, true))
				lvl--;
			else if (ft_istype (data->tab[i], T_PIPE, true)
				|| ft_istype (data->tab[i], T_OP, true))
			{
				if (ft_istype (data->tab[i], T_PIPE, true))
					inst = I_PIPE;
				else if (ft_istype (data->tab[i], T_OP_AND, true))
					inst = I_AND;
				else if (ft_istype (data->tab[i], T_OP_OR, true))
					inst = I_OR;
				j++;
			}
			else if (ft_istype (data->tab[i], T_REDIR, true))
				ft_catch (data, &i, j);
		}
		else
		{
			if (data->cmds[j].inst == I_UNDEF)
				data->cmds[j].inst = inst;
			if (data->cmds[j].lvl == -1)
				data->cmds[j].lvl = lvl;
			ft_catch (data, &i, j);
		}
		i++;
	}
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
			data->tab = ft_minishell_split (data, data->line);
			if (ft_assert_finished (data))
			{
				add_history (data->line);
				if (ft_isvalid (data))
				{
					ft_parse (data);
					ft_heredocs (data);
					ft_execute (data);	
				}
			}
		}
		ft_destroy_execution (data);
	}
	ft_destroy_data (data);
	return (EXIT_SUCCESS);
}

// more input
// probelm with (ls)
// awk
// wildcards perhaps tomorrow