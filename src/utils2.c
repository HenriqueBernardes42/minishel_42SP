/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:19:49 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/13 14:10:35 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_istypepl(char *str, t_type type, bool strict)
{
	if (ft_strncmp (str, "|", 1 + strict) == 0
		&& (type == T_SPECIAL || type == T_PIPE || type == T_CMD_CAT))
		return (1);
	else if (ft_strncmp (str, "&&", 2 + strict) == 0
		&& (type == T_SPECIAL || type == T_OP || type == T_OP_AND
			|| type == T_CMD_CAT))
		return (2);
	else if (ft_strncmp (str, "(", 1 + strict) == 0
		&& (type == T_SPECIAL || type == T_PARENTH_OPEN || type == T_PARENTH))
		return (1);
	else if (ft_strncmp (str, ")", 1 + strict) == 0
		&& (type == T_SPECIAL || type == T_PARENTH_CLOSE || type == T_PARENTH))
		return (1);
	return (0);
}

int	ft_istype(char *str, t_type type, bool strict)
{
	if (str == NULL)
		return (0);
	if (ft_strncmp (str, "<<", 2 + strict) == 0
		&& (type == T_SPECIAL || type == T_REDIR || type == REDIR_HEREDOC))
		return (2);
	else if (ft_strncmp (str, ">>", 2 + strict) == 0
		&& (type == T_SPECIAL || type == T_REDIR || type == REDIR_OUTFILE_APP))
		return (2);
	else if (ft_strncmp (str, "<", 1 + strict) == 0
		&& (type == T_SPECIAL || type == T_REDIR || type == REDIR_INFILE))
		return (1);
	else if (ft_strncmp (str, ">", 1 + strict) == 0
		&& (type == T_SPECIAL || type == T_REDIR || type == REDIR_OUTFILE_TRC))
		return (1);
	else if (ft_strncmp (str, ";", 1 + strict) == 0
		&& (type == T_SPECIAL || type == T_CMD_SEP || type == T_CMD_CAT))
		return (1);
	else if (ft_strncmp (str, "||", 2 + strict) == 0
		&& (type == T_SPECIAL || type == T_OP || type == T_OP_OR
			|| type == T_CMD_CAT))
		return (2);
	else
		return (ft_istypepl (str, type, strict));
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

static bool	ft_isexecutable(char *pathname)
{
	struct stat file_stat;

	stat (pathname, &file_stat);
	if (!S_ISREG (file_stat.st_mode))
		return (false);
	return (true);
}

char	*ft_pathname(t_data *data, char *name)
{
	int		i;
	char	*dir;
	char	*pathname;
	char	**path;

	ft_assert_not_null (data, data);
	ft_assert_not_null (data, name);
	if (access (name, X_OK) != -1 && ft_isexecutable (name))
		return (ft_strdup (name));
	i = -1;
	if (*ft_get_env_var(data->envp, "PATH") != NULL)
		path = ft_split(*ft_get_env_var(data->envp, "PATH") + 5, ':');
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
