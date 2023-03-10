/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:24:35 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/21 15:03:13 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_argsxp	*ft_initargsxp(t_data *data, int i, int c, int *arg_i)
{
	t_argsxp	*argsxp;

	argsxp = (t_argsxp *) malloc (sizeof (t_argsxp));
	if (argsxp == NULL)
		ft_throw (data, ERR_FAIL, "malloc", true);
	argsxp->data = data;
	if (i < 0)
		argsxp->i = 0;
	else
		argsxp->i = i;
	argsxp->c = c;
	argsxp->split = NULL;
	argsxp->arg_i_const = *arg_i;
	argsxp->arg_i = arg_i;
	argsxp->ntab = NULL;
	return (argsxp);
}

t_args4	*ft_initargs4(t_data *data)
{
	t_args4	*args4;

	args4 = (t_args4 *) malloc (sizeof (t_args4));
	if (args4 == NULL)
		ft_throw (data, ERR_FAIL, "malloc", true);
	args4->i = -1;
	args4->j = 0;
	args4->lvl = 0;
	args4->instr = I_START;
	return (args4);
}

t_args3	*ft_initargs3(t_data *data)
{
	t_args3	*args3;

	args3 = (t_args3 *) malloc (sizeof (t_args3));
	if (args3 == NULL)
		ft_throw (data, ERR_FAIL, "malloc", true);
	args3->i = 0;
	args3->status = 0;
	args3->q = 0;
	args3->opened = false;
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
