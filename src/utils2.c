/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: rburgsta <rburgsta@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:19:49 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/10 14:41:05 by rburgsta         ###   ########.fr       */
=======
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:19:49 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/12 12:01:59 by katchogl         ###   ########.fr       */
>>>>>>> katchogl
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_builtin(t_data *data, int i, char *builtin)
{
	if (ft_strncmp (builtin, "echo", 5) == 0)
		ft_echo (data, data->cmds[i].args);
	else if (ft_strncmp (builtin, "cd", 3) == 0)
	{
		if (data->cmds[i].argsc > 1)
			ft_cd (data, data->cmds[i].args[0]);
		else
			ft_cd (data, NULL);
	}
	else if (ft_strncmp (builtin, "pwd", 4) == 0)
		ft_pwd (data);
	else if (ft_strncmp (builtin, "export", 8) == 0)
		ft_export (data, data->cmds[i].args);
	else if (ft_strncmp (builtin, "unset", 7) == 0)
		ft_unset (data, data->cmds[i].args);
	else if (ft_strncmp (builtin, "env", 4) == 0)
		ft_env(data);
	else if (ft_strncmp (builtin, "exit", 5) == 0)
		ft_exit (data, data->cmds[i].args);
}

size_t	ft_tablen(char **tab)
{
	size_t	len;

	if (tab == NULL)
		return (0);
	len = 0;
	while (tab[len] != NULL)
		len++;
	return (len);
}

int	ft_isbuiltin(char *str)
{
	if (str == NULL)
		return (false);
	if (ft_strncmp (str, "echo", 5) == 0
		|| ft_strncmp (str, "pwd", 4) == 0
		|| ft_strncmp (str, "env", 4) == 0)
		return (1);
	else if (ft_strncmp (str, "exit", 5) == 0
		|| ft_strncmp (str, "export", 8) == 0
		|| ft_strncmp (str, "unset", 7) == 0
		|| ft_strncmp (str, "cd", 3) == 0)
		return (2);
	return (0);
}

static int	ft_istypepl(char *str, t_type type, bool strict)
{
	if (ft_strncmp (str, "|", 1 + strict) == 0
		&& (type == T_SPECIAL || type == T_PIPE || type == T_CMD_CAT))
		return (1);
	else if (ft_strncmp (str, "&&", 2 + strict) == 0
		&& (type == T_SPECIAL || type == T_OP || type == T_OP_AND
			|| type == T_CMD_CAT))
		return (2);
	else if (ft_strncmp (str, "(", 1 + strict) == 0
		&& (type == T_SPECIAL || type == T_PARENTH_OPEN || type == T_PARENTH))
		return (1);
	else if (ft_strncmp (str, ")", 1 + strict) == 0
		&& (type == T_SPECIAL || type == T_PARENTH_CLOSE || type == T_PARENTH))
		return (1);
	return (0);
}

int	ft_istype(char *str, t_type type, bool strict)
{
	if (str == NULL)
		return (0);
	if (ft_strncmp (str, "<<", 2 + strict) == 0
		&& (type == T_SPECIAL || type == T_REDIR || type == REDIR_HEREDOC))
		return (2);
	else if (ft_strncmp (str, ">>", 2 + strict) == 0
		&& (type == T_SPECIAL || type == T_REDIR || type == REDIR_OUTFILE_APP))
		return (2);
	else if (ft_strncmp (str, "<", 1 + strict) == 0
		&& (type == T_SPECIAL || type == T_REDIR || type == REDIR_INFILE))
		return (1);
	else if (ft_strncmp (str, ">", 1 + strict) == 0
		&& (type == T_SPECIAL || type == T_REDIR || type == REDIR_OUTFILE_TRC))
		return (1);
	else if (ft_strncmp (str, ";", 1 + strict) == 0
		&& (type == T_SPECIAL || type == T_CMD_SEP || type == T_CMD_CAT))
		return (1);
	else if (ft_strncmp (str, "||", 2 + strict) == 0
		&& (type == T_SPECIAL || type == T_OP || type == T_OP_OR
			|| type == T_CMD_CAT))
		return (2);
	else
		return (ft_istypepl (str, type, strict));
}
