/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_assert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhenriqu <hhenriqu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 02:42:14 by hhenriqu          #+#    #+#             */
/*   Updated: 2023/04/11 02:42:16 by hhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_update_line(t_data *data, char *linepl)
{
	char	*temp;

	temp = ft_strjoin (data->line, " ");
	free (data->line);
	data->line = ft_strjoin (temp, linepl);
	free (temp);
}

bool	ft_is_permission_denied(t_args *args, int permss, int i)
{
	if (((permss == R_OK || permss == X_OK)
			|| (permss == W_OK && i < args->count - 1))
		&& (access (args->path, F_OK) != 0
			|| access (args->path, permss) != 0))
		return (true);
	return (false);
}
