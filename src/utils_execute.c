/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:31:26 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/13 15:19:21 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_anticipate_cmdsc(t_data *data, int i)
{
	int	cmdsc;

	cmdsc = 1;
	while (++i < data->cmdsc && data->cmds[i].inst == I_PIPE)
		cmdsc++;
	return (cmdsc);
}

void	ft_pipe(t_data *data, int j, t_fd *iofd, t_stream s)
{
	t_fd	fd;

	if (data->pipes == NULL || data->cmdsc_pps <= 1
		|| (s == STREAM_INPUT && j < 1)
		|| (s == STREAM_OUTPUT && j == data->cmdsc_pps -1))
		return ;
	ft_assert_not_null (data, data);
	ft_assert_not_null (data, iofd);
	if (s == STREAM_INPUT)
		fd = data->pipes[(j - 1) * 2];
	else
		fd = data->pipes[(j * 2) + 1];
	if (dup2 (fd, *iofd) == -1)
		ft_throw (data, ERR_FAIL, "dup2", true);
	*iofd = fd;
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

void	ft_close_curr_lvl(t_data *data)
{
	int	j;

	j = -1;
	while (++j < data->cmdsc_pps)
	{
		wait (&data->status);
		if (WIFEXITED (data->status))
			data->status = WEXITSTATUS (data->status);
	}
	if (data->pipes != NULL)
	{
		free (data->pipes);
		data->pipes = NULL;
	}
}
