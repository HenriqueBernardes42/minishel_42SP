/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhenriqu <hhenriqu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 02:42:44 by hhenriqu          #+#    #+#             */
/*   Updated: 2023/04/11 02:42:46 by hhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_anticipate_cmdsc(t_data *data, int i)
{
	int	cmdsc;

	cmdsc = 1;
	while (++i < data->cmdsc && data->cmds[i].instr == I_PIPE)
		cmdsc++;
	return (cmdsc);
}

void	ft_close(t_data *data, int infd, int outfd)
{
	int		i;

	if (data->pipes == NULL)
		return ;
	ft_assert_not_null (data, data);
	i = -1;
	while (++i < (data->cmdsc_pps - 1) * 2)
		if (data->pipes[i] != infd && data->pipes[i] != outfd)
			close (data->pipes[i]);
}

void	ft_close_all(t_data *data)
{
	int		i;

	if (data->pipes == NULL)
		return ;
	ft_assert_not_null (data, data);
	i = -1;
	while (++i < (data->cmdsc_pps - 1) * 2)
		close (data->pipes[i]);
}

void	ft_close_curr_lvl(t_data *data, int temp_i)
{
	int	j;

	j = -1;
	while (++j < data->cmdsc_pps)
	{
		wait (&data->status);
		if (!ft_isbuiltin (data->cmds[temp_i].name)
			&& data->cmds[temp_i].pathname == NULL)
			data->status = EXIT_CMDNOTFOUND;
		else if (WIFEXITED (data->status))
		{
			data->status = WEXITSTATUS (data->status);
			temp_i++;
		}
		else if (ft_isbuiltin (data->cmds[temp_i].name) != 2)
		{
			data->status += 128;
		}
	}
	if (data->pipes != NULL)
	{
		free (data->pipes);
		data->pipes = NULL;
	}
}
