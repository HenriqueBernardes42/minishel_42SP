/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 05:44:06 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/03 14:37:54 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define PATH "PATH"
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_errno {
	ERR_UNDEF,
	ERR_NULL_CHECK_FAIL,
	ERR_MALLOC_FAIL,
	ERR_PIPE_FAIL,
	ERR_ENOENT,
	ERR_UNEXPECTED_TOKEN,
	ERR_C
} t_errno;
typedef enum e_redir {
	REDIR_NOT_FOUND,
	REDIR_IN_FILE,
	REDIR_IN_HEREDOC,
	REDIR_OUT_TRUNC,
	REDIR_OUT_APPEND
} t_redir;
typedef struct s_data
{
	char	**envp;
	char	**path;
	char	**input;
	char	*line;
}	t_data;
void	ft_assert_not_null(t_data *data, void *ptr);
bool	ft_throw(t_data *data, enum e_errno err, char *info, bool exitp);
char	*ft_cmdpath(t_data *data, char *name);
t_redir	ft_getredir(char *str);
void	ft_freeinput(t_data *data);
void	ft_freedata(t_data *data);
#endif