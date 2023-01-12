/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:23:25 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/12 10:37:21 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_upperlvl(t_data *data, int lvl, int *i, int *status)
{
	if (data->cmds[*i].inst == I_START
		|| (data->cmds[*i].inst == I_OR && *status != 0)
		|| (data->cmds[*i].inst == I_AND && *status == 0))
		ft_loop (data, data->cmds[*i].lvl, i);
	else
	{
		while (data->cmds[*i].lvl > lvl && *i < data->cmdsc)
			(*i)++;
	}
}

static void	ft_run(t_data *data, int *i, int *status)
{
	int	j;

	j = -1;
	while (++j < data->cmdsc_pps)
	{
		ft_child (data, *i, j);
		(*i)++;
	}
	if (data->pipes != NULL)
	{
		j = -1;
		while (++j < (data->cmdsc_pps - 1) * 2)
			close (data->pipes[j]);
	}
	j = -1;
	while (++j < data->cmdsc_pps)
		wait (status);
	if (data->pipes != NULL)
	{
		free (data->pipes);
		data->pipes = NULL;
	}
}

static void	ft_currentlvl(t_data *data, int *i, int *status)
{
	if (data->cmds[*i].inst == I_START
		|| (data->cmds[*i].inst == I_OR && *status != 0)
		|| (data->cmds[*i].inst == I_AND && *status == 0))
	{
		data->cmdsc_pps = ft_anticipate_cmdsc (data, *i);
		data->pipes = ft_initpipes (data, data->cmdsc_pps);
		ft_run (data, i, status);
	}
	else
		(*i)++;
}

bool	ft_loop(t_data *data, int lvl, int *i)
{
	int	status;

	ft_assert_not_null (data, data);
	status = 0;
	while (data->cmds[*i].lvl >= lvl && *i < data->cmdsc)
	{
		if (data->cmds[*i].lvl > lvl)
			ft_upperlvl (data, lvl, i, &status);
		else
			ft_currentlvl (data, i, &status);
	}
	return (true);
}

void	ft_execute(t_data *data)
{
	int	i;

	ft_assert_not_null (data, data);
	if (data->cmds == NULL)
		ft_throw (data, ERR_NULL_PTR, "ft_execute data->cmds", true);
	i = 0;
	ft_loop (data, 0, &i);
}
