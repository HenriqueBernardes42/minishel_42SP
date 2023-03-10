/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 21:40:47 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/24 17:27:40 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_destroy_args(t_args *args)
{
	if (args->path != NULL)
		free (args->path);
	if (args->tab != NULL)
		ft_destroy_tab (args->tab);
	free (args);
}

/// @brief Destroy, ie free an array of strings. 
/// @param tab The array of strings.
void	ft_destroy_tab(char **tab)
{
	int	i;

	if (tab == NULL)
		return ;
	i = -1;
	while (tab[++i] != NULL)
		free (tab[i]);
	free (tab);
}

/// @brief Destroy, ie free the array of comands.
/// @param tab The array of structs s_cmd.
static void	ft_destroy_cmds(t_data *data)
{
	int	i;

	if (data == NULL || data->cmds == NULL)
		return ;
	i = -1;
	while (++i < data->cmdsc)
	{
		if (data->cmds[i].name != NULL)
			free (data->cmds[i].name);
		if (data->cmds[i].pathname != NULL)
			free (data->cmds[i].pathname);
		if (data->cmds[i].args != NULL)
			ft_destroy_tab (data->cmds[i].args);
		if (data->cmds[i].args_redir != NULL)
			ft_destroy_tab (data->cmds[i].args_redir);
		if (data->cmds[i].redirs != NULL)
			free (data->cmds[i].redirs);
	}
	free (data->cmds);
}

/// @brief Destroy, ie free the memory allocated to execute the
/// minishell command and prepare for the execution of the next one.
/// @param data The minishell's data.
void	ft_destroy_execution(t_data *data)
{
	if (data->line != NULL)
		free (data->line);
	if (data->tab != NULL)
		ft_destroy_tab (data->tab);
	if (data->cmds != NULL)
		ft_destroy_cmds (data);
	if (data->pipes != NULL)
		free (data->pipes);
	data->line = NULL;
	data->tab = NULL;
	data->cmds = NULL;
	data->pipes = NULL;
	data->cmdsc = 0;
}

/// @brief Destroy the minishell's data, 
/// ie every byte of heap memory allocated.
/// @param data The minishell's data.
void	ft_destroy_data(t_data *data)
{
	if (data == NULL)
		return ;
	ft_destroy_execution (data);
	if (data->envp != NULL)
		ft_destroy_tab(data->envp);
	if (data->history != NULL)
		ft_destroy_tab(data->history);
	clear_history ();
	free (data);
}
