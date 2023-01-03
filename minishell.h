/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 05:44:06 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/03 22:13:57 by katchogl         ###   ########.fr       */
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

typedef enum e_errno {
	ERR_UNDEF,
	ERR_NULL_CHECK_FAIL,
	ERR_MALLOC_FAIL,
	ERR_PIPE_FAIL,
	ERR_FORK_FAIL,
	ERR_ENOENT,
	ERR_UNEXPECTED_TOKEN,
	ERR_INVALID_CMDSC,
	ERR_C
} t_errno;
typedef	int t_fd;
typedef	int t_pid;
typedef	struct s_cmd
{
	char	*name;
	char	*pathname;
	char	**args;
	char	**infiles;
	char	**heredoc_lims;
	char	**outfiles_trc;
	char	**outfiles_app;
} t_cmd;
typedef struct s_data
{
	char	**envp;
	char	**path;
	char	*line;
	char	**tab;
	t_cmd	*cmds;
	int		cmdsc;
}	t_data;
void	ft_execute(t_data *data); // tools
t_cmd	*ft_initcmds(t_data *data, int cmdsc); // init
t_data 	*ft_initdata(char **envp);
void	ft_assert_not_null(t_data *data, void *ptr); // utils
bool	ft_throw(t_data *data, enum e_errno err, char *info, bool exitp);
char	*ft_cmdpath(t_data *data, char *name);
void	ft_destroy_execution(t_data *data); // destroy
void	ft_destroy_data(t_data *data);
#endif