/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 05:44:06 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/02 20:09:00 by katchogl         ###   ########.fr       */
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
	ERR_NULL_CHECK_FAIL,
	ERR_MALLOC_FAIL,
	ERR_PIPE_FAIL,
	ERR_ENOENT,
	ERR_C
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
typedef struct	s_cmd
{
	struct s_cmd	*next;
}	t_cmd;
typedef struct s_exec
{
	t_cmd			**cmds;
	int 			cmdsc;
	struct s_exec	*next;
}	t_exec;
typedef struct s_data
{
	char			**envp;
	char			**path;
	char			*input;
	t_exec			**execs;
	int				execsc;
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