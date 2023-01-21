/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 21:46:13 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/21 15:45:46 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_getstr(t_data *data, char **tab, int index, char *var)
{
	char	*str;

	if ((*tab)[index] == '?')
		str = ft_itoa(data->status);
	else if (*ft_get_env_var(data->envp, var) != NULL)
		str = ft_strdup (*ft_get_env_var(data->envp, var) + ft_strlen(var) + 1);
	else
		str = ft_strdup ("");
	return (str);
}

int	ft_insert_var(t_data *data, char **tab, int index)
{
	char	*str;
	char	*var;
	int		i;
	int		c;

	i = (ft_isdigit((*tab)[index]) || tab[0][index] == '?');
	if (i == 0)
		while ((ft_isalnum((*tab)[index + i]) || (*tab)[index + i] == '_'))
			i++;
	var = ft_substr(*tab, index, i);
	str = ft_getstr (data, tab, index, var);
	free(var);
	var = (char *)malloc(ft_strlen(*tab) + ft_strlen(str) + 1);
	ft_strlcpy(var, *tab, index);
	ft_strlcat(var, str, ft_strlen(*tab) + ft_strlen(str) + 1);
	ft_strlcat(var, *tab + index + i, ft_strlen(*tab) + ft_strlen(str) + 1);
	c = ft_strlen (str);
	free(str);
	free(*tab);
	*tab = var;
	return (c);
}

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
