/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhenriqu <hhenriqu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:34:10 by hhenriqu          #+#    #+#             */
/*   Updated: 2023/03/13 18:41:57 by hhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	parse_variables(char *line, int *i)
{
	char	*var;

	var = NULL;
	if (line[*i + 1] == '?')
	{
		*i = *i + 1;
		var = ft_itoa(g_msh.exit_code);
		if (g_msh.parsed_line == NULL)
			g_msh.parsed_line = ft_strdup("");
		g_msh.parsed_line = ft_strjoin2(g_msh.parsed_line, var, 1, 1);
	}
	else if (ft_isdigit(line[*i + 1]))
		*i = *i + 1;
	else if (ft_isalpha(line[*i + 1]))
	{
		while (ft_isalpha(line[*i + 1]))
			var = ft_strcjoin(var, line[++*i]);
		g_msh.parsed_line = ft_strjoin2(\
			g_msh.parsed_line, ft_getenv(var), 1, 0);
		free(var);
	}
	else
		g_msh.parsed_line = ft_strcjoin(g_msh.parsed_line, line[*i]);
}

void	parse_quotes(char *line, int *i, char quote)
{
	g_msh.parsed_line = ft_strcjoin(g_msh.parsed_line, line[*i]);
	while (line[*i] != '\0')
	{
		if (quote == '\"' && line[*i] == '$')
			parse_variables(line, i);
		if (line[++*i] == quote)
		{
			g_msh.parsed_line = ft_strcjoin(g_msh.parsed_line, line[*i]);
			return ;
		}
		if (line[*i] != '\0')
		{
			if (quote == '\"' && line[*i] == '$')
				;
			else
				g_msh.parsed_line = ft_strcjoin(g_msh.parsed_line, line[*i]);
		}
	}
	write (STDOUT_FILENO, "Error: unclosed quotes\n", 24);
	g_msh.error = 1;
	g_msh.exit_code = 1;
}

void	parse_redirect(char *line, int *i, char redirect, int pos_heredoc)
{
	if (g_msh.file_name)
		free(g_msh.file_name);
	g_msh.file_name = NULL;
	g_msh.redirect = redirect;
	if (line[++*i] == redirect)
		*i = *i + 1;
	if (g_msh.here_doc == 1)
		*i = pos_heredoc;
	while (line[*i] == ' ')
		*i = *i + 1;
	if (check_syntax_error(line[*i]))
		return ;
	while (line[*i] && line[*i] != ' ' && line[*i] != '>' && line[*i] != '<')
	{
		g_msh.file_name = ft_strcjoin(g_msh.file_name, line[*i]);
		*i = *i + 1;
	}
	check_directory_error(g_msh.file_name);
	if (redirect == '>')
		open_file_output();
	else if (redirect == '<')
		open_file_input();
	if (line[*i] == '>' || line[*i] == '<')
		parse_redirect(line, i, line[*i], pos_heredoc);
}

int	handle_heredoc(char *line)
{
	int	i;
	int	get_pos;

	i = 0;
	get_pos = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '<')
		{
			if (line[++i] == '<')
			{
				g_msh.here_doc = 1;
				g_msh.doble_redirect = 1;
				get_pos = ++i;
			}
		}
		i++;
	}
	return (get_pos);
}
