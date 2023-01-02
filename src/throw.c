/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 07:02:09 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/02 16:19:04 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(t_data *data, bool all)
{
	ft_assert_not_null (data, data);
	if (all)
	{
		// free path
	}
	if (all)
		free (data);
}

void	ft_throw(t_data *data, enum e_errno err, char *info)
{
	printf ("\033[0;31mErr: ");
	if (err == ERR_NULL_CHECK_FAIL)
		printf ("null pointer");
	else if (err == ERR_ENOENT)
	{
		if (info != NULL)
			printf ("%s ", info);
		printf ("%s", strerror (ENOENT));
	}
	else
		printf ("an error occurred");
	printf ("\n\033[0m");
	ft_free (data, true);
	exit (EXIT_FAILURE);
}
