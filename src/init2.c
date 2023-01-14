/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:24:35 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/14 11:25:04 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_args4	*ft_initargs4(t_data *data)
{
	t_args4	*args4;

	args4 = (t_args4 *) malloc (sizeof (t_args4));
	if (args4 == NULL)
		ft_throw (data, ERR_FAIL, "malloc", true);
	args4->i = -1;
	args4->j = 0;
	args4->lvl = 0;
	args4->inst = I_START;
	return (args4);
}

t_args3	*ft_initargs3(t_data *data, char *str)
{
	t_args3	*args3;

	args3 = (t_args3 *) malloc (sizeof (t_args3));
	if (args3 == NULL)
		ft_throw (data, ERR_FAIL, "malloc", true);
	args3->str = str;
	args3->i = 0;
	args3->single_quote = false;
	args3->double_quote = false;
	return (args3);
}

int	*ft_initpipes(t_data *data, int cmdsc)
{	
	int	*pipes;
	int	i;

	if (cmdsc < 2)
		return (NULL);
	pipes = (int *) malloc ((cmdsc - 1) * 2 * sizeof (int));
	if (pipes == NULL)
		ft_throw (data, ERR_FAIL, "malloc", true);
	i = -1;
	while (++i < cmdsc - 1)
		if (pipe (pipes + i * 2) != 0)
			ft_throw (data, ERR_FAIL, "fail", true);
	return (pipes);
}
