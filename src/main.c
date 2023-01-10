/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 05:43:21 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/10 21:44:25 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_isvalid (t_data *data)
{
	int	i;
	bool open;
	
	ft_assert_not_null (data, data);
	ft_assert_not_null (data, data->tab);
	i = -1;
	open = false;
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
			if (open)
				return (ft_throw (data, ERR_UNEXPECTED_TOKEN,
					data->tab[i], false));
			else if (i != 0 && !ft_istype (data->tab[i - 1], T_CMD_CAT, true))
				return (ft_throw (data, ERR_UNEXPECTED_TOKEN,
					data->tab[i], false));
			else
				open = true;
		}
		else if(ft_istype (data->tab[i], T_PARENTH_CLOSE, true))
		{
			if (!open)
				return (ft_throw (data, ERR_UNEXPECTED_TOKEN,
					data->tab[i], false));
			else if (ft_istype (data->tab[i - 1], T_SPECIAL, true))
				return (ft_throw (data, ERR_UNEXPECTED_TOKEN,
					data->tab[i], false));
			else
				open = false;
		}
		else if (ft_istype (data->tab[i], T_CMD_SEP, true)
			&& open)
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

static void	ft_add_instruction(t_data *data, int i)
{
	ft_assert_not_null (data, data);
	if (ft_istype (data->tab[i], T_PIPE, true))
		ft_addint (data, &data->insts, data->insts_len, I_PIPE);
	else if (ft_istype (data->tab[i], T_OP_AND, true)
		|| ft_istype (data->tab[i], T_OP_OR, true))
	{
		if (i == 0)
			ft_throw (data, ERR_UNEXPECTED_TOKEN, data->tab[i], true);
		if (ft_istype (data->tab[i], T_OP_AND, true))
		{
			if (ft_istype (data->tab[i - 1], T_PARENTH, true)
				|| ft_istype (data->tab[i + 1], T_PARENTH, true))
				ft_addint (data, &data->insts, data->insts_len, I_AND_PARENTH);
			else
				ft_addint (data, &data->insts, data->insts_len, I_AND);
		}
		else
		{
			if (ft_istype (data->tab[i - 1], T_PARENTH, true)
				| ft_istype (data->tab[i + 1], T_PARENTH, true))
				ft_addint (data, &data->insts, data->insts_len, I_OR_PARENTH);
			else
				ft_addint (data, &data->insts, data->insts_len, I_OR);
		}
	}
	else
		ft_throw (data, ERR_FAIL, "add instruction", true);
	data->insts_len++;
}

/// @brief Parse the array of input to an array of structs of type s_cmd.
/// @param data The minishell's data.
static void	ft_parse(t_data *data)
{
	int	i;
	int	j;

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
	while (data->tab[i] != NULL && j < data->cmdsc)
	{
		while (data->tab[i] != NULL 
			&& !ft_istype (data->tab[i], T_PIPE, true)
			&& !ft_istype (data->tab[i], T_OP, true)) 
		{
			if (!ft_istype (data->tab[i], T_CMD_SEP, true)
				&& !ft_istype (data->tab[i], T_PARENTH, true))
				ft_catch (data, &i, j);
			i++;
		}
		if (data->tab[i] != NULL
			&& (ft_istype (data->tab[i], T_PIPE, true)
			|| ft_istype (data->tab[i], T_OP, true)))
		{
			ft_add_instruction (data, i);
			i++;
		}
		j++;
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
			add_history (data->line);
			data->tab = ft_minishell_split (data, data->line);
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
