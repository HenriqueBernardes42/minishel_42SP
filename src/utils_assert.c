/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_assert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:01:11 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/21 15:16:20 by katchogl         ###   ########.fr       */
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
