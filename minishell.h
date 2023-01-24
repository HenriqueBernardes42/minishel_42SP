/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 05:44:06 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/24 18:17:17 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <signal.h>
# include <errno.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/param.h>
# include <sys/stat.h>
# include <dirent.h>
# include <termios.h>
# define STDERR_FD STDERR_FILENO

bool		g_heredoc_success;
typedef enum e_signals
{
	SIG_PARENT,
	SIG_PARENT_EXECUTION,
	SIG_HEREDOC,
	SIG_CHILD,
}	t_signals;
typedef enum e_expand_str_type
{
	T_ENV,
	T_HOME
}	t_expand_str_type;
typedef enum e_exit
{
	EXIT_EXECUTABLE_PERM_DENIED = 126,
	EXIT_CMDNOTFOUND = 127,
	EXIT_SIGINT = 1,
	EXIT_SIGINT_CHILD = 130,
	EXIT_SIGQUIT_CHILD = 131,
	EXIT_UNEXPECTED_TOKEN = 258
}	t_exit;
typedef enum e_stream
{
	STREAM_INPUT,
	STREAM_OUTPUT
}	t_stream;
typedef enum e_type
{
	REDIR_UNDEF = -1,
	REDIR_INFILE,
	REDIR_HEREDOC,
	REDIR_OUTFILE_TRC,
	REDIR_OUTFILE_APP,
	T_REDIR,
	T_OP,
	T_PIPE,
	T_CMD_SEP,
	T_PARENTH,
	T_PARENTH_OPEN,
	T_PARENTH_CLOSE,
	T_OP_AND,
	T_OP_OR,
	T_CMD_CAT,
	T_SPECIAL
}	t_type;
typedef enum e_inst
{
	I_UNDEF = 9999,
	I_START,
	I_PIPE,
	I_AND,
	I_OR
}	t_inst;
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
	ERR_AMBIGUOUS_REDIRECT,
	ERR_UNEXPECTED_EOF
}	t_errno;
typedef int	t_fd;
typedef int	t_lvl;
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
	t_type	redir;
	t_fd	iofd;
	t_fd	infd;
	t_fd	outfd;
	t_fd	nfd;
	int		j;
}	t_args2;
typedef struct s_args3
{
	size_t	i;
	size_t	temp;
	int		status;
	char	q;
	bool	opened;
}	t_args3;
typedef struct s_args4
{
	int	i;
	int	j;
	int	lvl;
	int	instr;
}	t_args4;
typedef struct s_cmd
{
	char	*name;
	char	*pathname;
	char	**args;
	int		argsc;
	char	**args_redir;
	int		*redirs;
	int		redirsc;
	int		lvl;
	int		instr;
}	t_cmd;
typedef struct s_data
{
	char			**envp;
	char			*line;
	char			**tab;
	t_cmd			*cmds;
	int				cmdsc;
	t_fd			*pipes;
	int				cmdsc_pps;
	int				status;
	char			**history;
	int				where_history;
	struct termios	tty_attr;
}	t_data;
typedef struct s_argsxp
{
	t_data	*data;
	int		i;
	int		c;
	char	**split;
	int		*arg_i;
	int		arg_i_const;
	char	***ntab;
}	t_argsxp;
void		ft_execute(t_data *data);
t_cmd		*ft_initcmds(t_data *data, int cmdsc);
t_data		*ft_initdata(char **envp);
t_args		*ft_initargs(t_data *data, char *pathname);
t_args2		*ft_initargs2(t_data *data, int i);
t_args3		*ft_initargs3(t_data *data);
t_args4		*ft_initargs4(t_data *data);
bool		ft_throw(t_data *data, enum e_errno err, char *info, bool exitp);
char		*ft_pathname(t_data *data, char *name);
void		ft_push(t_data *data, char ***tab, char *str);
t_type		ft_getredir(char *str);
void		ft_destroy_execution(t_data *data);
void		ft_destroy_data(t_data *data);
void		ft_destroy_tab(char **tab);
void		ft_addint(t_data *data, int **arr, int len, int i);
void		ft_heredocs(t_data *data);
void		ft_remove(t_data *data, char ***tab, char *str);
int			ft_isbuiltin(char *str);
void		ft_exec_builtin(t_data *data, int i, char *builtin);
void		ft_echo(t_data *data, char **args);
void		ft_cd(t_data *data, char *path);
void		ft_pwd(t_data *data);
void		ft_unset(t_data *data, char **args);
void		ft_exit(t_data *data, char **args);
void		ft_export(t_data *data, char **args);
void		ft_env(t_data *data);
bool		ft_minishell_split(t_data *data, char *str);
int			ft_istype(char *str, t_type type, bool strict);
int			*ft_initpipes(t_data *data, int cmdsc);
size_t		ft_tablen(char **tab);
bool		ft_assert_finished(t_data *data);
bool		ft_isvalid(t_data *data);
void		ft_close(t_data *data, int infd, int outfd);
void		ft_child(t_data *data, int i, int j);
int			ft_anticipate_cmdsc(t_data *data, int i);
char		**ft_get_env_var(char **envp, char *var);
bool		ft_valid_env_name(char *str);
void		ft_parse(t_data *data);
char		*ft_memdup(char const *s, size_t a, size_t b);
bool		ft_matches_pattern(char *pattern, char *filename);
void		ft_close_curr_lvl(t_data *data, int temp_i);
void		ft_push_special(t_data *data, t_args3 *args3, char *str);
void		ft_update_line(t_data *data, char *linepl);
void		ft_shift(t_data *data, char ***tab, char *str);
void		ft_explode_name(t_data *data, int i);
void		ft_addhistory(t_data *data, char *line);
void		ft_remove_last_history(t_data *data);
void		ft_assert_not_null(t_data *data, void *ptr);
bool		ft_assert_not_dir(t_data *data, char *pathname, bool exitp);
bool		ft_assert_valid_permissions(t_data *data, char *pathname,
				int permss, bool exitp);
void		ft_redirect(t_data *data, int i);
void		ft_close_all(t_data *data);
void		ft_putinfo(char *str, char *info, char *str2);
void		ft_insert_home_dir(t_data *data, char **tab, int index);
void		ft_expand_str(t_data *data, char **str, char ***tab, int arg_i);
void		ft_expand_tab(t_data *data, char ***tab);
void		ft_remove_quote(t_data *data, bool *quote, char **str,
				int index);
void		ft_signals(t_signals signals);
t_argsxp	*ft_initargsxp(t_data *data, int i, int c, int *arg_i);
int			ft_push_substr_wildcard(t_data *data, char *pattern);
void		ft_str_remove_quotes(t_data *data, char **str);
bool		ft_isfinished(t_data *data);
bool		ft_is_permission_denied(t_args *args, int permss, int i);
void		ft_destroy_args(t_args *args);
bool		ft_explode_env(t_data *data, char ***str, char ***tab,
				t_argsxp *argsxp);
int			ft_insert_var(t_data *data, char **tab, int index);
void		ft_loop(t_data *data, int lvl, int *i);
bool		ft_iswhitespace(char c);
void		ft_ar_env_var(t_data *data, char *args);
void		ft_update_shlvl(t_data *data);
#endif