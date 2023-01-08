/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 16:39:27 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/08 10:53:43 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_setnfd(t_data *data, t_args2 *args2)
{
	ft_assert_not_null (data, data);
	ft_assert_not_null (data, args2);
	if (args2->redir == REDIR_INFILE)
		args2->nfd = open (data->cmds[args2->i].args_redir[args2->j],
				O_RDONLY); // first check if file exits if yes use elsecheck if matches
				// any pattern, if yes ambiguous else no such file
	else if (args2->redir == REDIR_HEREDOC)
		args2->nfd = ft_atoi (data->cmds[args2->i]
				.args_redir[args2->j]);
	else if (args2->redir == REDIR_OUTFILE_TRC)
		args2->nfd = open (data->cmds[args2->i].args_redir[args2->j],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (args2->redir == REDIR_OUTFILE_APP)
		args2->nfd = open (data->cmds[args2->i].args_redir[args2->j],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
}

static void	ft_prepare(t_data *data, t_args2 *args2)
{
	ft_assert_not_null (data, data);
	ft_assert_not_null (data, args2);
	args2->nfd = -1;
	args2->iofd = args2->infd;
	if (args2->redir != REDIR_INFILE && args2->redir != REDIR_HEREDOC)
		args2->iofd = args2->outfd;
}

static void	ft_assert_valid_files(t_data *data, int i)
{
	int	permss;
	int	j;

	j = -1;
	while (++j < data->cmds[i].redirsc)
	{
		if (data->cmds[i].redirs[j] == REDIR_INFILE
			|| data->cmds[i].redirs[j] == REDIR_OUTFILE_TRC
			|| data->cmds[i].redirs[j] == REDIR_OUTFILE_APP)
		{
			permss = R_OK;
			if (data->cmds[i].redirs[j] != REDIR_INFILE)
				permss = W_OK;
			ft_assert_not_dir (data, data->cmds[i].args_redir[j]);
			ft_assert_valid_permissions (data,
				data->cmds[i].args_redir[j], permss);
		}
	}
}

void	ft_redirect(t_data *data, int i, t_fd *infd, t_fd *outfd)
{
	t_args2	*args2;

	if (data->cmds[i].redirsc < 1)
		return ;
	ft_assert_not_null (data, data);
	ft_assert_not_null (data, data->cmds[i].redirs);
	ft_assert_valid_files (data, i);
	args2 = ft_initargs2 (data, i, infd, outfd);
	while (--args2->j >= 0)
	{
		args2->redir = data->cmds[args2->i].redirs[args2->j];
		ft_prepare (data, args2);
		ft_setnfd (data, args2);
		if (args2->nfd == -1)
			ft_throw (data, ERR_ENOENT, NULL, true);
		if (dup2 (args2->nfd, *args2->iofd) != -1)
			*args2->iofd = args2->nfd;
		else
			ft_throw (data, ERR_FAIL, "ft_redirect dup2", true);
	}
	free (args2);
}
