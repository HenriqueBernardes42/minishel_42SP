/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fcntrl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 19:58:43 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/06 20:37:50 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_redir	ft_getredir(char *str)
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

static void	ft_write(int fd, char *heredoc_lim, char *buff, int count)
{
	char	*lim;

	lim = ft_strnstr (buff, heredoc_lim, count);
	if (lim != NULL && *(lim - 1) == '\n'
		&& *(lim + ft_strlen (heredoc_lim) - 1) == '\n'
		&& *(lim + ft_strlen (heredoc_lim)) == '\0')
	{
		count = 0;
		while (buff[count] != heredoc_lim[0])
			count++;
	}
	write (fd, buff, count);
}

t_fd	ft_heredoc(t_data *data, char *heredoc_lim)
{
	t_fd	fd;
	char	buff[BUFFER_SIZE];
	int		count;

	fd = open ("temp.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ft_assert_not_equal (data, fd, -1, ERR_FILE_WRITE_CREATE_FAIL);
	while (1)
	{
		ft_putstr_fd ("here_doc> ", STDOUT_FILENO);
		count = read (STDIN_FILENO, buff, BUFFER_SIZE - 1);
		if (count <= 0)
			break ;
		else
		{
			buff[count] = '\0';
			if (ft_strncmp (buff, heredoc_lim, count) != 0)
				ft_write (fd, heredoc_lim, buff, count);
			else
				break ;
		}
	}
	close (fd);
	fd = open ("temp.tmp", O_RDONLY, 0644);
	unlink ("temp.tmp");
	return (fd);
}
