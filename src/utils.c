/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 11:22:19 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/03 14:52:21 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_cmdpath(t_data *data, char *name)
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

t_redir	ft_getredir(char *str)
{
	if (ft_strncmp (str, "<", 2) != 0)
		return (REDIR_IN_FILE);
	else if (ft_strncmp (str, ">", 2) != 0)
		return (REDIR_IN_FILE);
	else if (ft_strncmp (str, "<<", 3) != 0)
		return (REDIR_IN_FILE);
	else if (ft_strncmp (str, ">>", 3) != 0)
		return (REDIR_IN_FILE);
	else
		return (REDIR_NOT_FOUND);
}

void	ft_assert_not_null(t_data *data, void *ptr)
{
	if (ptr == NULL)
		ft_throw (data, ERR_NULL_CHECK_FAIL, NULL, true);
}

bool	ft_throw(t_data *data, enum e_errno err, char *info, bool exitp)
{
	char	**errors;

	errors = (char *[ERR_C]){"an error occurred",
		"null check fail",
		"failed to allocate heap memory", "failed to initialize pipe",
		strerror (ERR_ENOENT),
		"syntax error near unexpected token"};
	printf ("minishell: ");
	if (info != NULL && err == ERR_ENOENT)
		printf ("%s ", info);
	if (err >= ERR_UNDEF && err < ERR_C)
		printf ("%s", errors[err]);
	else
		printf ("an unexpected error occurred");
	if (info != NULL && err == ERR_UNEXPECTED_TOKEN)
		printf (" `%s'", info);
	printf ("\n\033[0m");
	if (exitp)
	{
		ft_freedata (data);
		exit (EXIT_FAILURE);
	}
	return (false);
}
