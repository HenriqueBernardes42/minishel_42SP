/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 05:43:21 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/12 12:43:05 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Check whether the array of input strings is valid or not.
/// @param data The minishell's data;
/// @return the result.
static bool	ft_isvalid(t_data *data)
{
	int		i;

	ft_assert_not_null (data, data);
	ft_assert_not_null (data, data->tab);
	if (ft_istype (data->tab[0], T_PIPE)
		|| ft_istype (data->tab[0], T_CMD_SEP))
		return (ft_throw (data, ERR_UNEXPECTED_TOKEN, data->tab[0], false));
	i = -1;
	while (data->tab[++i] != NULL)
	{
		if ((ft_istype (data->tab[i], T_SPECIAL)
				&& ft_istype (data->tab[i + 1], T_SPECIAL))
			|| (ft_istype (data->tab[i], T_CMD_SEP)
				&& data->tab[i + 1] != NULL))
			return (ft_throw (data, ERR_UNEXPECTED_TOKEN,
					data->tab[i + 1], false));
		else if ((ft_istype (data->tab[i], T_REDIR) || ft_istype
				(data->tab[i], T_PIPE)) && data->tab[i + 1] == NULL)
			return (ft_throw (data, ERR_UNEXPECTED_TOKEN,
					"(null)", false));
	}
	return (true);
}

/// @brief Catch or set the members of the current command's struct.
/// @param data The minishell's data;
/// @param i The pointer to the index of the current input string in data->tab;
/// @param j The index of the current command.
static void	ft_catch(t_data *data, int *i, int j)
{
	t_redir	redir;

	ft_assert_not_null (data, data);
	redir = ft_getredir (data->tab[*i]);
	if (redir != REDIR_UNDEF)
	{
		ft_addint (data, &data->cmds[j].redirs, data->cmds[j].redirsc, redir);
		data->cmds[j].redirsc++;
		(*i)++;
		if (data->tab[*i] != NULL)
			ft_push (data, &data->cmds[j].args_redir, data->tab[*i]);
	}
	else if (data->cmds[j].name == NULL)
	{
		data->cmds[j].name = ft_strdup (data->tab[*i]);
		data->cmds[j].pathname = ft_pathname (data, data->cmds[j].name);
		ft_push (data, &data->cmds[j].args, data->cmds[j].pathname);
		data->cmds[j].argsc++;
	}
	else
	{
		ft_push (data, &data->cmds[j].args, data->tab[*i]);
		data->cmds[j].argsc++;
	}
}

/// @brief Parse the array of input to an array of structs of type s_cmd.
/// @param data The minishell's data.
static void	ft_parse(t_data *data)
{
	int	i;
	int	j;

	ft_assert_not_null (data, data);
	ft_assert_not_null (data, data->tab);
	i = -1;
	data->cmdsc = 1;
	while (data->tab[++i] != NULL)
		if (ft_strncmp (data->tab[i], "|", 2) == 0)
			data->cmdsc++;
	data->cmds = ft_initcmds (data, data->cmdsc);
	i = 0;
	j = 0;
	while (data->tab[i] != NULL && j < data->cmdsc)
	{
		while (data->tab[i] != NULL && ft_strncmp (data->tab[i], "|", 2) != 0)
		{
			if (!ft_istype (data->tab[i], T_CMD_SEP))
				ft_catch (data, &i, j);
			i++;
		}
		if (data->tab[i] != NULL && ft_strncmp (data->tab[i], "|", 2) == 0)
			i++;
		j++;
	}
}

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
			while (data->line[i + i2] != ' ' && data->line[i + i2] != '\0')
			if (data->line[i + ++i2] == '\"')
				ign = !ign;
		tmp = ft_substr(data->line, i, i2);
		ft_push(data, &data->tab, tmp);
		free(tmp);
		i += i2;
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
		if (data->line != NULL && ft_strncmp (data->line, "", 1) != 0)
		{
			//data->tab = ft_split (data->line, ' ');
			ft_split_input(data);
			ft_expand (data);
			//Debug
			int i = -1;
			while (data->tab[++i] != NULL)
				printf("'%s' ", data->tab[i]);
			printf("'%p'\n", data->tab[i]);
			if (ft_isvalid (data))
			{
				ft_parse (data);
				ft_heredocs (data);
				ft_execute (data);
			}
			add_history (data->line);
		}
		else if (data->line == NULL)
			ft_exit(data, NULL);
		ft_destroy_execution (data);
	}
	ft_destroy_data (data);
	return (EXIT_SUCCESS);
}
