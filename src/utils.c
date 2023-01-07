/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 11:22:19 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/07 16:42:39 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_addint(t_data *data, int **arr, int len, int n)
{
	int	*narr;
	int	i;

	if (len <= 0 || *arr == NULL)
		len = 1;
	else
		len += 1;
	narr = (int *) malloc (len * sizeof (int));
	ft_assert_not_null (data, narr);
	if (*arr != NULL)
	{
		i = -1;
		while (++i < len - 1)
			narr[i] = (*arr)[i];
	}
	narr[len - 1] = n;
	free (*arr);
	*arr = narr;
}

void	ft_push(t_data *data, char ***tab, char *str)
{
	char	**ntab;
	int		size_tab;
	int		i;

	if (str == NULL)
		return ;
	size_tab = 0;
	if (*tab != NULL)
	{
		i = -1;
		while ((*tab)[++i] != NULL)
			size_tab++;
	}
	ntab = (char **) malloc ((size_tab + 2) * sizeof (char *));
	if (ntab == NULL)
		ft_throw (data, ERR_NULL_PTR, "ft_push ntab", true);
	i = -1;
	while (++i < size_tab)
		ntab[i] = ft_strdup ((*tab)[i]);
	ntab[i] = ft_strdup (str);
	ntab[i + 1] = NULL;
	if (*tab == NULL)
		ft_destroy_tab (*tab);
	*tab = ntab;
}

static void	ft_error(t_errno err)
{
	if (err == ERR_DEFAULT)
		printf ("something went wrong");
	else if (err == ERR_NULL_PTR)
		printf ("null pointer");
	else if (err == ERR_FAIL)
		printf ("fail");
	else if (err == ERR_UNEXPECTED_TOKEN)
		printf ("unexpected token near");
	else if (err == ERR_INVALID_CMDSC)
		printf ("invalid count of commands");
	else if (err == ERR_CMD_NOT_FOUND)
		printf ("command not found");
	else if (err == ERR_ENOENT)
		printf ("%s", strerror (ENOENT));
	else if (err == ERR_EACCES)
		printf ("%s", strerror (EACCES));
	else if (err == ERR_EISDIR)
		printf ("%s", strerror (EISDIR));
	else if (err != 0)
		printf ("an unexpected error occurred");
}

bool	ft_throw(t_data *data, enum e_errno err, char *info, bool exitp)
{
	printf ("minishell: ");
	if (info != NULL && (err == ERR_CMD_NOT_FOUND
			|| err == ERR_EACCES || err == ERR_ENOENT))
		printf ("%s: ", info);
	else if (info != NULL && err == ERR_FAIL)
		printf ("%s ", info);
	ft_error (err);
	if (info != NULL && err == ERR_UNEXPECTED_TOKEN)
		printf (" `%s'", info);
	if (info != NULL && err != ERR_UNEXPECTED_TOKEN
		&& err != ERR_ENOENT && err != ERR_CMD_NOT_FOUND
		&& err != ERR_EACCES && err != ERR_FAIL)
		printf (": `%s'", info);
	printf ("\n");
	if (exitp)
	{
		ft_destroy_data (data);
		exit (EXIT_FAILURE);
	}
	return (false);
}
