/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 05:42:32 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/02 19:51:34 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static 

bool	ft_parse(t_data *data)
{
	char	**tab;

	ft_assert_not_null (data, data);
	tab = ft_split (data->input, " ");
	

	
	free (tab);
	return (true);
}

// cmd
// 
// has next (cmd)
