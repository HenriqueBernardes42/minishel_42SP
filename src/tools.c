/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:23:25 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/06 09:46:11 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_logcmds(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->cmdsc)
	{
		if (&(data->cmds[i]) != NULL)
		{
			printf ("------ cmd -----: \n");
			if (data->cmds[i].name != NULL)
				printf ("name: %s\n", data->cmds[i].name);
			else
				printf ("no name");
			if (data->cmds[i].pathname != NULL)
				printf ("pathname: %s\n", data->cmds[i].pathname);
			else
				printf ("no pathname");
			if (data->cmds[i].args != NULL)
			{
				printf ("args:\n");
				j = -1;
				while (data->cmds[i].args[++j] != NULL)
					printf ("%s \n", data->cmds[i].args[j]);
			}
			if (data->cmds[i].infiles != NULL)
			{
				printf ("\ninfiles:\n");
				if (data->cmds[i].infiles)
				j = -1;
				while (data->cmds[i].infiles[++j] != NULL)
					printf ("%s \n", data->cmds[i].infiles[j]);
			}
			if (data->cmds[i].heredoc_lims != NULL)
			{
				printf ("\nhereooc_lims:\n");
				j = -1;
				while (data->cmds[i].heredoc_lims[++j] != NULL)
					printf ("%s \n", data->cmds[i].heredoc_lims[j]);
			}
			if (data->cmds[i].outfiles_trc != NULL)
			{
				printf ("\noutfiles_trc:\n");
				j = -1;
				while (data->cmds[i].outfiles_trc[++j] != NULL)
					printf ("%s \n", data->cmds[i].outfiles_trc[j]);
			}
			if (data->cmds[i].outfiles_app != NULL)
			{
				printf ("\noutfiles_app:\n");
				j = -1;
				while (data->cmds[i].outfiles_app[++j] != NULL)
					printf ("%s \n", data->cmds[i].outfiles_app[j]);
			}
		}
		else
			printf ("command args is null \n");
	}
}

void	ft_execute(t_data *data)
{
	ft_assert_not_null (data, data);
	ft_logcmds (data);
}
