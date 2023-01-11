/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:19:49 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/11 18:40:40 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtin(t_data *data, int i, char *builtin)
{
	if (ft_strncmp (builtin, "echo", 5) == 0)
		ft_echo (data->cmds[i].args);
	else if (ft_strncmp (builtin, "cd", 3) == 0)
	{
		if (data->cmds[i].argsc > 1)
			ft_cd (data, data->cmds[i].args[1]);
		else
			ft_cd (data, NULL); // go to user root dir (~/)
	}
	else if (ft_strncmp (builtin, "pwd", 4) == 0)
		ft_pwd (data);
	else if (ft_strncmp (builtin, "export", 7) == 0)
		ft_export (data, data->cmds[i].args);
	else if (ft_strncmp (builtin, "unset", 6) == 0)
		ft_unset (data, data->cmds[i].args);
	else if (ft_strncmp (builtin, "env", 4) == 0)
		ft_env(data);
	else if (ft_strncmp (builtin, "exit", 5) == 0)
		ft_exit (data);
}

char	*ft_getinput(t_data *data)
{
	ft_assert_not_null (data, data);
	return (NULL);
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
