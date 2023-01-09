/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:39:17 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/09 23:23:12 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

bool	ft_isbuiltin(char *str)
{
	if (str == NULL)
		return (false);
	if (ft_strncmp (str, "echo", 5) == 0
		|| ft_strncmp (str, "cd", 3) == 0
		|| ft_strncmp (str, "pwd", 4) == 0
		|| ft_strncmp (str, "export", 7) == 0
		|| ft_strncmp (str, "unset", 6) == 0
		|| ft_strncmp (str, "env", 4) == 0
		|| ft_strncmp (str, "exit", 5) == 0)
		return (true);
	return (false);
}

bool	ft_istype(char *str, t_type type, bool strict)
{
	if (str == NULL)
		return (0);
	if (ft_strncmp (str, "<", 1 + strict) == 0
		&& (type == T_SPECIAL || type == T_REDIR || type == REDIR_INFILE))
		return (1);
	else if (ft_strncmp (str, "<<", 2 + strict) == 0
		&& (type == T_SPECIAL || type == T_REDIR || type == REDIR_HEREDOC))
		return (2);
	else if (ft_strncmp (str, ">", 1 + strict) == 0
		&& (type == T_SPECIAL || type == T_REDIR || type == REDIR_OUTFILE_TRC))
		return (1);
	else if (ft_strncmp (str, ">>", 2 + strict) == 0
		&& (type == T_SPECIAL || type == T_REDIR || type == REDIR_OUTFILE_APP))
		return (2);
	else if (ft_strncmp (str, ";", 1 + strict) == 0
		&& (type == T_SPECIAL || type == T_CMD_SEP))
		return (1);
	else if (ft_strncmp (str, "|", 1 + strict) == 0
		&& (type == T_SPECIAL || type == T_PIPE))
		return (1);
	else if ((ft_strncmp (str, "&&", 2 + strict) == 0 
		|| ft_strncmp (str, "||", 2 + strict) == 0)
		&& (type == T_SPECIAL || type == T_OP))
		return (2);
	else if ((ft_strncmp (str, "(", 1 + strict) == 0
		|| ft_strncmp (str, ")", 1 + strict) == 0)
		&& (type == T_SPECIAL || type == T_OP))
		return (1);
	return (0);
}
