/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 21:46:13 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/20 19:51:00 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_insert_home_dir(t_data *data, char **tab, int index)
{
	char	*var;
	char	*str;

	if (*ft_get_env_var(data->envp, "HOME") != NULL)
		str = *ft_get_env_var(data->envp, "HOME") + 5;
	else
		str = "";
	var = (char *)malloc(ft_strlen(*tab) + ft_strlen(str) + 1);
	ft_strlcpy(var, *tab, index);
	ft_strlcat(var, str, ft_strlen(*tab) + ft_strlen(str) + 1);
	ft_strlcat(var, *tab + index, ft_strlen(*tab) + ft_strlen(str) + 1);
	free(*tab);
	*tab = var;
}

// buggy
// bool	ft_split_add_tab(t_data *data, char ***str, char ***tab,
// 	t_argsxp *argsxp)
// {
// 	char	**ntab;
// 	int		i;

// 	if (data == NULL || str == NULL || tab == NULL || argsxp == NULL)
// 		return (false);
// 	ntab = ft_subtab (data, *tab, 0, *argsxp->arg_i);
// 	ft_push (data, &ntab, argsxp->split[0]);
// 	if (ft_tablen (argsxp->split) > 2)
// 	{
// 		i = 0;
// 		while (++i < (int) ft_tablen (argsxp->split) - 1)
// 		{
// 			ft_push (data, &ntab, argsxp->split[i]);
// 			(*argsxp->arg_i)++;
// 		}
// 	}
// 	ft_push (data, &ntab, argsxp->split 
// 		[ft_tablen (argsxp->split) - 1]);
// 	(*argsxp->arg_i)++;
// 	*str = &ntab[*argsxp->arg_i];
// 	while ((*tab)[++argsxp->arg_i_const] != NULL)
// 		ft_push (data, &ntab, (*tab)[argsxp->arg_i_const]);
// 	ft_destroy_tab (*tab);
// 	*tab = ntab;
// 	return (true);
// }

bool	ft_cut_str(t_data *data, char ***str, char ***tab,
	t_argsxp *argsxp)
{
	char	**split;
	char	*substr;
	
	if (data == NULL || str == NULL || tab == NULL || argsxp == NULL)
		return (false);
	substr = ft_substr (**str, argsxp->i, argsxp->c);
	if (substr == NULL)
		return (false);
	split = ft_split (substr, ' ');
	if (split == NULL)
		return (false);
	if (ft_tablen (split) > 1)
	{
		argsxp->split = split;
		ft_putendl_fd (argsxp->split[0], 2);
		ft_putendl_fd (argsxp->split[1], 2);
		return (ft_split_add_tab (data, str, tab, argsxp));
	}
	free (substr);
	ft_destroy_tab (split);
	free (argsxp);
	return (false);
}