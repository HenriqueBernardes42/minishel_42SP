/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 07:02:09 by katchogl          #+#    #+#             */
/*   Updated: 2022/12/23 20:04:39 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(t_data *data, t_bool all)
{
	ft_assert_not_null (data, data);
	if (all)
	{
		// free path
	}
	if (all)
		free (data);
}

void	ft_throw(t_data *data, enum e_errno err, t_err_info *info)
{
	printf ("\033[0;31mErr: ");
	if (err == ERR_NULL_CHECK_FAIL)
		printf ("null pointer");
	else if (err == ERR_ENOENT)
	{
		if (info != NULL && info->file != NULL)
			printf ("%s ", info->file);
		printf ("%s", strerror (ENOENT));
	}
	else
		printf ("an error occurred");
	printf ("\n\033[0m");
	ft_free (data, TRUE);
	exit (EXIT_FAILURE);
}
