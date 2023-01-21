/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 21:46:13 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/21 12:22:29 by rburgsta         ###   ########.fr       */
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

bool	ft_split_add_tab(t_data *data, char ***str, char ***tab,
	t_argsxp *argsxp)
{
	int		i;
	char	**ntab;
	char	*substr2;
	char	*temp;

	if (data == NULL || str == NULL || tab == NULL || argsxp == NULL)
		return (false);
	ntab = NULL;
	i = -1;
	while (++i < *argsxp->arg_i)
		ft_push (data, &ntab, (*tab)[i]);
	substr2 = ft_substr (**str, 0, argsxp->i);
	temp = ft_strjoin (substr2, argsxp->split[0]);
	ft_push (data, &ntab, temp);
	free (substr2);
	free (temp);
	if (ft_tablen (argsxp->split) > 2)
	{
		i = 0;
		while (++i < (int) ft_tablen (argsxp->split) - 1)
		{
			ft_push (data, &ntab, argsxp->split[i]);
			(*argsxp->arg_i)++;
		}
	}
	substr2 = ft_substr (**str, argsxp->i + argsxp->c, ft_strlen (**str));
	temp = ft_strjoin (argsxp->split[ft_tablen (argsxp->split) - 1],
			substr2);
	ft_push (data, &ntab, temp);
	(*argsxp->arg_i)++;
	free (substr2);
	free (temp);
	i = argsxp->arg_i_const;
	while ((*tab)[++i] != NULL)
		ft_push (data, &ntab, (*tab)[i]);
	free (*tab);
	*tab = ntab;
	free (**str);
	*str = &(*tab)[*argsxp->arg_i];
	return (true);
}

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
		return (ft_split_add_tab (data, str, tab, argsxp));
	}
	free (substr);
	ft_destroy_tab (split);
	free (argsxp);
	return (false);
}
