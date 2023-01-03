/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:23:25 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/03 20:16:38 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expand(t_data *data)
{
	ft_assert_not_null (data, data);
}

// static void	ft_redirect_out(t_data *data)
// {
// 	ft_assert_not_null (data, data);
// }

static void	ft_redirect_in(t_data *data)
{
	ft_assert_not_null (data, data);
}

void	ft_execute(t_data *data)
{
	int	i;
	int	j;

	ft_assert_not_null (data, data);
	i = -1;
	while (data->cmds[++i] != NULL)
	{
		r
		// each command amongst pipes
		j = -1;
		while (data->cmds[i][++j] != NULL)
		{
			// each element in the command's tab
		}
	}
}
