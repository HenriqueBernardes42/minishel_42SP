/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_explode_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 15:13:44 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/21 15:35:40 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_split_add_tab_start(t_data *data, char ***str, char ***tab,
	t_argsxp *argsxp)
{
	int		i;
	char	*substr;
	char	*temp;

	i = -1;
	while (++i < *argsxp->arg_i)
		ft_push (data, argsxp->ntab, (*tab)[i]);
	substr = ft_substr (**str, 0, argsxp->i);
	temp = ft_strjoin (substr, argsxp->split[0]);
	ft_push (data, argsxp->ntab, temp);
	free (substr);
	free (temp);
}

static void	ft_split_add_tab_end(t_data *data, char ***str, char ***tab,
	t_argsxp *argsxp)
{
	int		i;
	char	*substr;
	char	*temp;

	substr = ft_substr (**str, argsxp->i + argsxp->c, ft_strlen (**str));
	temp = ft_strjoin (argsxp->split[ft_tablen (argsxp->split) - 1],
			substr);
	ft_push (data, argsxp->ntab, temp);
	(*argsxp->arg_i)++;
	free (substr);
	free (temp);
	i = argsxp->arg_i_const;
	while ((*tab)[++i] != NULL)
		ft_push (data, argsxp->ntab, (*tab)[i]);
	free (*tab);
	*tab = *argsxp->ntab;
	free (**str);
	*str = &(*tab)[*argsxp->arg_i];
}

static bool	ft_split_add_tab(t_data *data, char ***str, char ***tab,
	t_argsxp *argsxp)
{
	int		i;
	char	**ntab;

	if (data == NULL || str == NULL || tab == NULL || argsxp == NULL)
		return (false);
	ntab = NULL;
	argsxp->ntab = &ntab;
	ft_split_add_tab_start (data, str, tab, argsxp);
	if (ft_tablen (argsxp->split) > 2)
	{
		i = 0;
		while (++i < (int) ft_tablen (argsxp->split) - 1)
		{
			ft_push (data, &ntab, argsxp->split[i]);
			(*argsxp->arg_i)++;
		}
	}
	ft_split_add_tab_end (data, str, tab, argsxp);
	return (true);
}

bool	ft_explode_env(t_data *data, char ***str, char ***tab,
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
