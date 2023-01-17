/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 21:46:13 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/17 22:36:41 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_isenv_var(char *str)
{
	int	i;

	if (str == NULL || str[0] != '$')
		return (false);
	i = -1;
	while (str[++i] != '\0')
		if (str[i] == ' ')
			return (false);
	return (true);
}

static int	ft_split_add_env(t_data *data, char ***ntab, char *env)
{
	int		i;
	char	**env_tab;

	if (ntab == NULL || env == NULL)
		ft_throw (data, ERR_NULL_PTR, NULL, true);
	env_tab = ft_split (*ft_get_env_var 
		(data->envp, env) + ft_strlen (env) + 1, ' ');
	if (env_tab == NULL)
	{
		ft_push (data, ntab, "");
		return (1);
	}
	i = -1;
	while (env_tab[++i] != NULL)
		ft_push (data, ntab, env_tab[i]);
	ft_destroy_tab (env_tab);
	return (i);
}

int ft_expand_env_var(t_data *data, char ***tab, int i)
{
	char	**ntab;
	int		j;
	int		c;

	if (tab == NULL)
		ft_throw (data, ERR_NULL_PTR, NULL, true);
	ntab = NULL;
	j = -1;
	c = 0;
	while ((*tab)[++j] != NULL)
	{
		if (j != i)
			ft_push (data, &ntab, (*tab)[j]);
		else
			c += ft_split_add_env (data, &ntab, (*tab)[j] + 1);
	}
	ft_destroy_tab (*tab);
	*tab = ntab;
	return (c);
}