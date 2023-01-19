/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 05:43:21 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/19 14:52:28 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_readline(t_data *data)
{
	ft_assert_not_null (data, data);
	data->read_state = true;
	data->line = readline ("\001\033[32;1m\002minishell$ \001\033[0m\002");
	data->read_state = false;
}

static void	ft_mainpl(t_data *data)
{
	ft_assert_not_null (data, data);
	ft_addhistory (data, data->line);
	if (ft_minishell_split (data, data->line) && ft_isvalid (data)
		&& ft_assert_finished (data))
	{
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
	ft_init_signal_handler(data);
	while (true)
	{
		data->tty_attr.c_lflag &= ~ECHOCTL;
    	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &data->tty_attr) != 0)
			ft_throw (data, ERR_FAIL, "main settattr fail", true);
		ft_readline (data);
		if (data->line == NULL)
			ft_exit(data, NULL);
		else if (ft_strncmp (data->line, "", 1) != 0)
			ft_mainpl (data);
		ft_destroy_execution (data);
	}
	ft_destroy_data (data);
	exit (EXIT_SUCCESS);
}
