/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 05:43:21 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/12 16:20:16 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_insert_var(t_data *data, char **tab, int index)
{
	char	*str;
	char	*var;
	int		i;
	
	i = 0;
	while (ft_isalnum(tab[0][index + i]) || tab[0][index + i] == '_')
		i++;
	var = ft_substr(*tab, index, i);
	if (*get_env_var(data->envp, var) != NULL)
		str = *get_env_var(data->envp, var) + ft_strlen(var) + 1;
	else
		str = "";
	free(var);
	var = (char *)malloc(ft_strlen(*tab) + ft_strlen(str));
	ft_strlcpy(var, *tab, index);
	ft_strlcat(var, str, ft_strlen(*tab) + ft_strlen(str));
	ft_strlcat(var, *tab + index + i, ft_strlen(*tab) - ft_strlen(str));
	free(*tab);
	*tab = var;
}

static void	ft_expand(t_data *data)
{
	int	ign;
	int	i;
	int	i2;

	ft_assert_not_null (data, data);
	i = -1;
	ign = 0;
	while (data->tab[++i] != NULL)
	{
		i2 = -1;
		while (data->tab[i][++i2] != '\0')
		{
			if (data->tab[i][i2] == '\'')
				ign = !ign;	
			else if (data->tab[i][i2] == '$' && !ign)
				ft_insert_var(data, data->tab + i, i2 + 1);
		}
	}
}

void	ft_split_input(t_data *data)
{
	int	i;
	int	i2;
	char *tmp;
	int	ign;

	i = -1;
	ign = 0;
	while (data->line[++i] != '\0')
	{
		i2 = 0;
		if (!ign)
		{
			while (!ign && data->line[i + i2] != ' ' && data->line[i + i2] != '\0')
				if (data->line[i + ++i2] == '\"')
					ign = !ign;
		}
		else if (ign)
		{
			while (data->line[i + i2] != '\"' && data->line[i + i2] != '\0')
				i2++;
			ign = !ign;
		}
		tmp = ft_substr(data->line, i, i2);
		ft_push(data, &data->tab, tmp);
		free(tmp);
		i += i2;
	}
}

static void	ft_exec(t_data *data)
{
	ft_assert_not_null (data, data);
	data->tab = ft_minishell_split (data, data->line);
	//ft_split_input(data);
	ft_expand(data);
	// Debug
	// int i = -1;
	// while (data->tab[++i] != NULL)
	// 	printf("'%s' ", data->tab[i]);
	// printf("'%p'\n", data->tab[i]);
	if (ft_isvalid (data) && ft_assert_finished (data))
	{
		add_history (data->line);
		ft_parse (data);
		ft_heredocs (data);
		ft_execute (data);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	if (argc != 1 || argv == NULL || envp == NULL)
		return (EXIT_FAILURE);
	data = ft_initdata (envp);
	init_signal_handler();
	while (true)
	{
		data->line = readline ("\033[32;1mminishell$ \033[0m");
		if (data->line == NULL)
			ft_exit(data, NULL);
		else if (ft_strncmp (data->line, "", 1) != 0)
			ft_exec (data);
		ft_destroy_execution (data);
	}
	ft_destroy_data (data);
	return (EXIT_SUCCESS);
}
