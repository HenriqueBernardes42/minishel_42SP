/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 05:44:06 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/02 16:21:13 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

enum e_errno {
	ERR_UNDEF,
	ERR_NULL_CHECK_FAIL = 1,
	ERR_MALLOC_FAIL,

	ERR_PIPE_FAIL = 10,
	ERR_ENOENT = 15
};
enum e_type {
	T_UNDEF,
	T_CMD,
	T_CMD_ARG,
	T_PIPE,
	T_REDIR_IN,
	T_HEREDOC,
	T_REDIR_OUT_TRUNC,
	T_REDIR_OUT_APPEND
};
typedef enum e_errno	t_errno;
typedef struct	s_arg
{
	char			*str;
	enum e_type		type;
	struct s_arg	**args;
	int				argc;
}	t_arg;
typedef struct s_data
{
	char			**envp;
	char			**path;
	char			*input;
	int				argc;
	t_arg			**args;
}	t_data;
void	ft_assert_not_null(t_data *data, void *ptr);
void	ft_free(t_data *data, bool all);
bool	ft_parse(t_data *data);
void	ft_throw(t_data *data, enum e_errno err, char *info);
void	ft_setpath(t_data *data);
char	*ft_cmdpath(t_data *data, char *name);
t_data 	*ft_initdata();
void	ft_exec(t_data *data);
#endif