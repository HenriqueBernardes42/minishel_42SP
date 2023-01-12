/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 11:22:19 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/12 13:49:54 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_remove(t_data *data, char ***tab, char *str)
{
	char	**ntab;
	int		size_tab;
	int		i;

	if (str == NULL)
		return ;
	size_tab = 0;
	i = -1;
	if (*tab != NULL)
		while ((*tab)[++i] != NULL)
			if (ft_strncmp(str, (*tab)[i], ft_strlen(str) + 1))
				size_tab++;
	ntab = (char **)malloc((size_tab + 1) * sizeof (char *));
	if (ntab == NULL)
		ft_throw(data, ERR_FAIL, "malloc", true);
	ntab[size_tab] = NULL;
	while (--size_tab >= 0)
	{
		if (!ft_strncmp(str, (*tab)[--i], ft_strlen(str) + 1))
			i--;
		ntab[size_tab] = ft_strdup ((*tab)[i]);
	}
	ft_destroy_tab(*tab);
	*tab = ntab;
}

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
	if (*tab != NULL)
		ft_destroy_tab (*tab);
	*tab = ntab;
}

t_type	ft_getredir(char *str)
{
	if (ft_strncmp (str, "<", 2) == 0)
		return (REDIR_INFILE);
	else if (ft_strncmp (str, ">", 2) == 0)
		return (REDIR_OUTFILE_TRC);
	else if (ft_strncmp (str, "<<", 3) == 0)
		return (REDIR_HEREDOC);
	else if (ft_strncmp (str, ">>", 3) == 0)
		return (REDIR_OUTFILE_APP);
	return (REDIR_UNDEF);
}

char	*ft_pathname(t_data *data, char *name)
{
	int		i;
	char	*dir;
	char	*pathname;
	char	**path;

	ft_assert_not_null (data, data);
	ft_assert_not_null (data, name);
	if (access (name, X_OK) != -1)
		return (ft_strdup (name));
	i = -1;
	if (*get_env_var(data->envp, "PATH") != NULL)
		path = ft_split(*get_env_var(data->envp, "PATH") + 5, ':');
	else
		return (NULL);
	while (path[++i] != NULL)
	{
		dir = ft_strjoin (path[i], "/");
		pathname = ft_strjoin (dir, name);
		free (dir);
		if (access (pathname, X_OK) != -1)
			return (ft_destroy_tab(path), pathname);
		free (pathname);
	}
	ft_destroy_tab(path);
	return (NULL);
}
