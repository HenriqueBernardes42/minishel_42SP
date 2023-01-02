/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 06:41:40 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/02 18:19:01 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_assert_not_null(t_data *data, void *ptr)
{
	if (ptr == NULL)
		ft_throw (data, ERR_NULL_CHECK_FAIL, NULL);
}
