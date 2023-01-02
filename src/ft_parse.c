/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 05:42:32 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/02 20:27:05 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_parse(t_data *data)
{
	const char	**tab;
	int			i;

	ft_assert_not_null (data, data);
	tab = (const char **) ft_split (data->input, ' ');
	i =-1;
	while (tab[++i] != NULL)
		printf ("elem: [%s]\n", tab[i]);
	free (tab);
	return (true);
}

// cmd
// |
// ->	(linker) = pipe/redirection app/ redirection 
// ->	(cmd) next -> 
// echo "hello world" < file cat
// cat file < file cat | cat file < file cat echo --> fetched last elem, ignored middle ones
// cat outputs multiple files

// still redirection but input is ignored
// cat file << file2 file3 file4
// > hello
// > world
// > file2
// hello
// hello3
// hello4
//cat file << file2 << EOF file3 file4


// all indirections are done first no matter where they are one after the other
// all outdirecyions are done last no matter where they are one after the other sweeping outfiles