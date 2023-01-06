/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:23:25 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/06 13:46:57 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_include_pipes(t_data *data, int i)
{
	
}

static void	ft_redirect_io(t_data *data, int i)
{
	int		j;
	t_fd	infd;
	t_fd	outfd;
	
	infd = STDIN_FILENO;
	outfd = STDOUT_FILENO;
	j = -1;
	while (++j < data->cmds[i].redirsc)
	{
		if ((data->cmds[i].redirs[j] == REDIR_INFILE
				|| data->cmds[i].redirs[j] == REDIR_HEREDOC)
			&& infd != STDIN_FILENO)
			close (infd);
		else if ((data->cmds[i].redirs[j] == REDIR_OUTFILE_TRC
				|| data->cmds[i].redirs[j] == REDIR_OUTFILE_APP)
			&& infd != STDOUT_FILENO)
			close (outfd);
		ft_handle_redirection (data, i, &infd, &outfd); 
	}
	ft_include_pipes ()
	// check pipes
	// if not defs edit 
}

static void	ft_child(t_data *data, int i)
{
	t_pid	pid;
	t_fd	in_fd;
	t_fd	out_fd;
	int		res[2];

	ft_assert_not_null (data, data);
	ft_assert_not_null (data, data->cmds);
	pid = fork ();
	if (pid == -1)
		ft_throw (data, ERR_FORK_FAIL, "ft_child", true);
	if (pid == 0)
	{
		if (data->cmds[i].redirs != NULL)
			ft_redirect_io (data, i);
		if (data->cmds[i].pathname != NULL)
		{
			execve (data->cmds[i].pathname
				, data->cmds[i].args, data->envp);
			ft_throw (data, ERR_EXECVE_FAIL, NULL, true);
		}
		else
			ft_throw (data, ERR_INVALID_CMD, data->cmds[i].name, true);
	}
}

void	ft_execute(t_data *data)
{
	int	i;

	ft_assert_not_null (data, data);
	if (data->cmds == NULL)
		ft_throw (data, ERR_NULL_PTR, "ft_execute data->cmds", true);
	i = -1;
	if (data->cmdsc > 1)
	{
		data->pipes = (t_fd *) malloc ((data->cmdsc - 1) * 2 * sizeof (t_fd));
		ft_assert_not_null (data, data->pipes);
		i = -1;
		while (++i < data->cmdsc)
			if (pipes (data->pipes + i) == -1);
				ft_throw (data, ERR_PIPE_FAIL, "ft_execute", true);
	}
	while (++i < data->cmdsc)
		ft_run_child (data, i);
	wait (NULL); // TODO: improve
}
