/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 21:31:29 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/02 21:39:51 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_ispipe(char *str)
{
	return (ft_strncmp (str, "|", 2) == 0);
}

bool	ft_isinredir(char *str)
{
	return (ft_strncmp (str, "<", 2) == 0);
}

bool	ft_isoutredir_trc(char *str)
{
	return (ft_strncmp (str, ">", 2) == 0);
}

bool	ft_isoutredir_app(char *str)
{
	return (ft_strncmp (str, ">>", 3) == 0);
}
