/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhenriqu <hhenriqu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:33:58 by hhenriqu          #+#    #+#             */
/*   Updated: 2023/02/17 14:33:59 by hhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	free_cmds_lst(void)
{
	t_dlist	*tmp;
	int		i;

	while (g_msh.cmds_lst != NULL)
	{
		tmp = g_msh.cmds_lst;
		i = -1;
		while (((char **)tmp->content)[++i])
			free(((char **)tmp->content)[i]);
		g_msh.cmds_lst = g_msh.cmds_lst->next;
		free(tmp->content);
		free(tmp);
	}
	free(g_msh.cmds_lst);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = -1;
	while (matrix[++i] != NULL)
		free(matrix[i]);
	free(matrix);
}

void	free_all(void)
{
	free(g_msh.parsed_line);
	free(g_msh.prompt);
	ft_dlstclear(&g_msh.envp_lst, &free);
	free_cmds_lst();
	close(g_msh.save_stdin);
	close(g_msh.save_stdout);
	close(g_msh.fd[0]);
	close(g_msh.fd[1]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	rl_clear_history();
}
