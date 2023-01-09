/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 05:44:06 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/09 17:59:35 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/param.h>
# include <sys/wait.h>
# define BUFFER_SIZE 42

typedef enum e_stream
{
	STREAM_INPUT,
	STREAM_OUTPUT
}	t_stream;
typedef enum e_redir
{
	REDIR_UNDEF = -1,
	REDIR_INFILE,
	REDIR_HEREDOC,
	REDIR_OUTFILE_TRC,
	REDIR_OUTFILE_APP,
}	t_redir;
typedef enum e_type
{
	T_REDIR = 4,
	T_CMD_SEP,
	T_PIPE,
	T_SPECIAL
}	t_type;
typedef enum e_errno {
	ERR_DEFAULT = 1,
	ERR_NULL_PTR,
	ERR_UNEXPECTED_TOKEN,
	ERR_INVALID_CMDSC,
	ERR_CMD_NOT_FOUND,
	ERR_FAIL,
	ERR_ENOENT,
	ERR_EACCES,
	ERR_EISDIR,
	ERR_AMBIGUOUS_REDIRECT
}	t_errno;
typedef int	t_fd;
typedef int	t_wstatus;
typedef struct s_args
{
	char	**tab;
	int		count;
	char	*path;
	char	*temp;
	int		err;
}	t_args;
typedef struct s_args2
{
	int		i;
	t_redir	redir;
	t_fd	*iofd;
	t_fd	nfd;
	int		j;
	t_fd	*infd;
	t_fd	*outfd;
}	t_args2;
typedef struct s_cmd
{
	char	*name;
	char	*pathname;
	char	**args;
	int		argsc;
	char	**args_redir;
	int		*redirs;
	int		redirsc;
}	t_cmd;
typedef struct s_data
{
	char		**envp;
	char		**path;
	char		*line;
	char		**tab;
	t_cmd		*cmds;
	int			cmdsc;
	t_fd		*pipes;
	pid_t		*pids;
	int			foreground_pipe;
}	t_data;
void	ft_execute(t_data *data);
t_cmd	*ft_initcmds(t_data *data, int cmdsc);
t_data	*ft_initdata(char **envp);
t_args	*ft_initargs(t_data *data, char *pathname);
t_args2	*ft_initargs2(t_data *data, int i, t_fd *infd, t_fd *outfd);
void	ft_assert_not_null(t_data *data, void *ptr);
void	ft_assert_not_dir(t_data *data, char *pathname);
void	ft_assert_valid_permissions(t_data *data, char *pathname, int permss);
bool	ft_throw(t_data *data, enum e_errno err, char *info, bool exitp);
char	*ft_pathname(t_data *data, char *name);
void	ft_push(t_data *data, char ***tab, char *str);
t_redir	ft_getredir(char *str);
void	ft_destroy_execution(t_data *data);
void	ft_destroy_data(t_data *data);
void	ft_destroy_tab(char **tab);
void	ft_addint(t_data *data, int **arr, int len, int i);
void	ft_redirect(t_data *data, int i, t_fd *infd, t_fd *outfd);
void	ft_heredocs(t_data *data);
void	ft_remove(t_data *data, char ***tab, char *str);
int		ft_isbuiltin(char *str);
void	ft_builtin(t_data *data, int i, char *builtin);
void	ft_echo(char **args);
void	ft_cd(t_data *data, char *path);
void	ft_pwd(t_data *data);
void	ft_unset(t_data *data, char **args);
void 	ft_exit(t_data *data, char **args);
void	ft_env(t_data *data);
void	ft_export(t_data *data, char **args);
bool	ft_istype(char *str, t_type type);

void	init_signal_handler(void);
#endif