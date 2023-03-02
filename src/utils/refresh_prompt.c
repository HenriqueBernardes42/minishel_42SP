/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhenriqu <hhenriqu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:34:27 by hhenriqu          #+#    #+#             */
/*   Updated: 2023/02/19 20:22:20 by hhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static char	*get_dir(char *cwd)
{
	char	**dir;
	char	*ret;
	int		i;

	i = -1;
	if (ft_strcmp(cwd, "/"))
		return (ft_strdup("/"));
	dir = ft_split(cwd, '/');
	while (dir[++i])
		if (dir[i + 1] == NULL)
			ret = ft_strdup(dir[i]);
	free_matrix(dir);
	return (ret);
}

char	*refresh_prompt(void)
{
	char	*prompt;
	char	cwd[PATH_MAX];

	if (g_msh.prompt)
		free(g_msh.prompt);
	prompt = ft_strjoin2(ft_getenv("USER"), " at minisell in ", 0, 0);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		prompt = ft_strjoin2(prompt, get_dir(cwd), 1, 1);
	g_msh.prompt = ft_strjoin2(prompt, "> ", 1, 0);
	return (g_msh.prompt);
}
