/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 11:22:19 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/06 09:21:56 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_throw (data, ERR_NULL_CHECK_FAIL, "ft_push ntab", true);
	i = -1;
	while (++i < size_tab)
		ntab[i] = ft_strdup ((*tab)[i]);
	ntab[i] = ft_strdup (str);
	ntab[i + 1] = NULL;
	if (*tab == NULL)
		ft_destroy_tab (*tab);
	*tab = ntab;
}

void	ft_assert_not_null(t_data *data, void *ptr)
{
	if (ptr == NULL)
		ft_throw (data, ERR_NULL_CHECK_FAIL, NULL, true);
}

char	*ft_pathname(t_data *data, char *name)
{
	int		i;
	char	*dir;
	char	*pathname;

	ft_assert_not_null (data, data);
	ft_assert_not_null (data, name);
	if (access (name, X_OK) != -1)
		return (ft_strdup (name));
	i = -1;
	if (data->path == NULL)
		return (NULL);
	while (data->path[++i] != NULL)
	{
		dir = ft_strjoin (data->path[i], "/");
		pathname = ft_strjoin (dir, name);
		free (dir);
		if (access (pathname, X_OK) != -1)
			return (pathname);
		free (pathname);
	}
	return (NULL);
}

bool	ft_throw(t_data *data, enum e_errno err, char *info, bool exitp)
{
	char	**errors;

	errors = (char *[ERR_C]){"an error occurred", "null pointer",
		"failed to allocate heap memory", "pipe fail", "fork fail",
		strerror (ENOENT), "syntax error near unexpected token",
		"invalid commands' count"};
	printf ("minishell: ");
	if (info != NULL && err == ERR_ENOENT)
		printf ("%s ", info);
	if (err >= ERR_UNDEF && err < ERR_C)
		printf ("%s", errors[err]);
	else
		printf ("an unexpected error occurred");
	if (info != NULL && err == ERR_UNEXPECTED_TOKEN)
		printf (" `%s'", info);
	if (info != NULL && err != ERR_UNEXPECTED_TOKEN
		&& err != ERR_ENOENT)
		printf (": `%s'", info);
	printf ("\n\033[0m");
	if (exitp)
	{
		ft_destroy_data (data);
		exit (EXIT_FAILURE);
	}
	return (false);
}
