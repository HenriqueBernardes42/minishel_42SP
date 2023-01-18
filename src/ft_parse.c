/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:08:41 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/17 16:50:40 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_catch_redir(t_data *data, t_args4 *args4, t_type redir)
{
	ft_assert_not_null (data, data);
	ft_assert_not_null (data, args4);
	ft_addint (data, &data->cmds[args4->j].redirs,
		data->cmds[args4->j].redirsc, redir);
	data->cmds[args4->j].redirsc++;
	args4->i++;
	if (data->tab[args4->i] != NULL)
		ft_push (data, &data->cmds[args4->j].args_redir,
			data->tab[args4->i]);
}

static void	ft_catch(t_data *data, t_args4 *args4)
{
	t_type	redir;

	ft_assert_not_null (data, data);
	ft_assert_not_null (data, args4);
	redir = ft_getredir (data->tab[args4->i]);
	if (redir != REDIR_UNDEF)
		ft_catch_redir (data, args4, redir);
	else if (data->cmds[args4->j].name == NULL)
		data->cmds[args4->j].name = ft_strdup (data->tab[args4->i]);
	else
	{
		ft_push (data, &data->cmds[args4->j].args, data->tab[args4->i]);
		data->cmds[args4->j].argsc++;
	}
}

static void	ft_handle_specials(t_data *data, t_args4 *args4)
{
	ft_assert_not_null (data, data);
	ft_assert_not_null (data, args4);
	if (ft_istype (data->tab[args4->i], T_PARENTH_OPEN, true))
		args4->lvl++;
	else if (ft_istype (data->tab[args4->i], T_PARENTH, true))
		args4->lvl--;
	else if (ft_istype (data->tab[args4->i], T_PIPE, true)
		|| ft_istype (data->tab[args4->i], T_OP, true))
	{
		if (ft_istype (data->tab[args4->i], T_PIPE, true))
			args4->instr = I_PIPE;
		else if (ft_istype (data->tab[args4->i], T_OP_AND, true))
			args4->instr = I_AND;
		else if (ft_istype (data->tab[args4->i], T_OP_OR, true))
			args4->instr = I_OR;
		args4->j++;
	}
	else if (ft_istype (data->tab[args4->i], T_REDIR, true))
		ft_catch (data, args4);
}

static void	ft_handle_type(t_data *data, t_args4 *args4)
{
	ft_assert_not_null (data, data);
	ft_assert_not_null (data, args4);
	if (ft_istype (data->tab[args4->i], T_SPECIAL, true))
		ft_handle_specials (data, args4);
	else
	{
		if (data->cmds[args4->j].instr == I_UNDEF)
			data->cmds[args4->j].instr = args4->instr;
		if (data->cmds[args4->j].lvl == -1)
			data->cmds[args4->j].lvl = args4->lvl;
		ft_catch (data, args4);
	}
	args4->i++;
}

void	ft_parse(t_data *data)
{
	t_args4	*args4;

	ft_assert_not_null (data, data);
	ft_assert_not_null (data, data->tab);
	args4 = ft_initargs4 (data);
	data->cmdsc = 1;
	args4->i = -1;
	while (data->tab[++args4->i] != NULL)
		if (ft_istype (data->tab[args4->i], T_PIPE, true)
			|| ft_istype (data->tab[args4->i], T_OP, true))
			data->cmdsc++;
	data->cmds = ft_initcmds (data, data->cmdsc);
	args4->i = 0;
	while (data->tab[args4->i] != NULL && args4->j < data->cmdsc)
		ft_handle_type (data, args4);
	free (args4);
}
