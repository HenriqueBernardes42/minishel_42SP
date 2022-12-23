/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 19:45:27 by katchogl          #+#    #+#             */
/*   Updated: 2022/12/23 20:05:00 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data 	*ft_initdata(void)
{
	t_data	*data;

	data = (t_data *) malloc (sizeof (t_data));
	ft_assert_not_null (data, data);
	data->envp = NULL;
	data->path = NULL;
	data->input = NULL;
	data->args = NULL;
	data->argc = -1;
	return (data);
}
