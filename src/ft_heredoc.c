/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 17:41:10 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/07 19:44:42 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool ft_isheredoc_lim(char *heredoc_lim, char *buff)
{
	char	*heredoc_limendl;
		
	if (heredoc_lim != NULL && buff != NULL)
	{
		heredoc_limendl = ft_strjoin (heredoc_lim, "\n");
		if (heredoc_limendl != NULL)
		{
			if (ft_strncmp (heredoc_limendl, buff,
				ft_strlen (heredoc_limendl) + 1) == 0)
			{
				free (heredoc_lim);
				return (true);
			}
			free (heredoc_limendl);
		}
	}
	return (false);
}

static void	ft_read(int fd, char *heredoc_lim)
{
	char	buff[BUFFER_SIZE];
	int		count;

	while (1)
	{
		ft_putstr_fd ("> ", STDERR_FILENO);
		count = read (STDIN_FILENO, buff, BUFFER_SIZE - 1);
		if (count <= 0)
			break ;
		else
		{
			buff[count] = '\0';
			if (!ft_isheredoc_lim (heredoc_lim, buff))
				write (fd, buff, count);
			else
				break ;
		}
	}
}

t_fd	ft_heredoc(t_data *data, char *heredoc_lim)
{
	t_fd	fd;

	if (heredoc_lim == NULL)
		return (-1);
	fd = open ("temp.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		ft_throw (data, ERR_FAIL, "file write", true);
	ft_read(fd, heredoc_lim);
	close (fd);
	fd = open ("temp.tmp", O_RDONLY, 0644);
	unlink ("temp.tmp");
	return (fd);
}
