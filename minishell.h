/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 05:44:06 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/06 20:41:24 by katchogl         ###   ########.fr       */
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
# include <fcntl.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# define BUFFER_SIZE 42

typedef enum e_stream
{
	STREAM_INPUT,
	STREAM_OUTPUT
} t_stream;
typedef enum e_redir
{
	REDIR_UNDEF = -1,
	REDIR_INFILE,
	REDIR_HEREDOC,
	REDIR_OUTFILE_TRC,
	REDIR_OUTFILE_APP,
} t_redir;
typedef enum e_errno {
	ERR_UNDEF,
	ERR_NULL_PTR,
	ERR_MALLOC_FAIL,
	ERR_PIPE_FAIL,
	ERR_FORK_FAIL,
	ERR_ENOENT,
	ERR_UNEXPECTED_TOKEN,
	ERR_INVALID_CMDSC,
	ERR_DUP2_FAIL,
	ERR_CMD_NOT_FOUND,
	ERR_EXECVE_FAIL,
	ERR_INVALID_STREAM,
	ERR_EISDIR,
	ERR_FILE_WRITE_CREATE_FAIL,
	ERR_C
} t_errno;
typedef	int t_fd;
typedef	int t_pid;
typedef	struct s_cmd
{
	char	*name;
	char	*pathname;
	char	**args;
	char	**args_redir;
	int		*redirs;
	int		redirsc;
} t_cmd;
typedef struct s_data
{
	char	**envp;
	char	**path;
	char	*line;
	char	**tab;
	t_cmd	*cmds;
	int		cmdsc;
	t_fd	*pipes;
}	t_data;
typedef struct s_args
{
	char	**tab;
	int		count;
	char	*path;
	char	*temp;
	int		err;
}	t_args;
void	ft_execute(t_data *data); // tools
t_cmd	*ft_initcmds(t_data *data, int cmdsc); // init
t_data 	*ft_initdata(char **envp);
t_args	*ft_initargs(t_data *data, char *pathname);
void	ft_assert_not_null(t_data *data, void *ptr); // assert
void	ft_assert_not_dir(t_data *data, char *pathname);
void	ft_assert_valid_permissions(t_data *data, char *pathname, int permss);
void	ft_assert_not_equal(t_data *data, int self, int value, t_errno err);
bool	ft_throw(t_data *data, enum e_errno err, char *info, bool exitp); // utils
char	*ft_pathname(t_data *data, char *name);
void	ft_push(t_data *data, char ***tab, char *str);
t_redir	ft_getredir(char *str);
void	ft_destroy_execution(t_data *data); // destroy
void	ft_destroy_data(t_data *data);
void	ft_destroy_tab(char **tab);
void	ft_addint(t_data *data, int **arr, int len, int i); // utils2
t_fd	ft_heredoc(t_data *data, char *heredoc_lim);
#endif