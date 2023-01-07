/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 17:41:10 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/07 18:13:43 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	ft_read(int fd, char *heredoc_lim)
{
	char	buff[BUFFER_SIZE];
	int		count;

	while (1)
	{
		ft_putstr_fd ("> ", STDOUT_FILENO);
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
}

t_fd	ft_heredoc(t_data *data, char *heredoc_lim)
{
	t_fd	fd;

	fd = open ("temp.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		ft_throw (data, ERR_FAIL, "file write", true);
	ft_read(fd, heredoc_lim);
	close (fd);
	fd = open ("temp.tmp", O_RDONLY, 0644);
	unlink ("temp.tmp");
	return (fd);
}
