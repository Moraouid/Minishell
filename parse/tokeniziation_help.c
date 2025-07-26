/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniziation_help.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 04:05:31 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/07/26 09:35:44 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token_status	update_quote_status(t_token_status status, char c)
{
	if (c == '\'' && status == DEFAULT)
		return (SQUOTE);
	if (c == '"' && status == DEFAULT)
		return (DQUOTE);
	if (c == '\'' && status == SQUOTE)
		return (DEFAULT);
	if (c == '"' && status == DQUOTE)
		return (DEFAULT);
	return (status);
}

int	identify_type(char *str, int i)
{
	if (str[i] == '|')
		return (PIPE);
	if (str[i] == '<')
	{
		if (str[i + 1] == '<')
			return (HEREDOC);
		return (INPUT);
	}
	if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			return (APPEND);
		return (OUTPUT);
	}
	if (is_space(str[i]))
		return (SPACES);
	if (str[i] == '\0')
		return (END);
	return (WORD);
}

int	is_separator(char *str, int i)
{
	t_token_type	type;

	type = identify_type(str, i);
	if (type == PIPE || type == INPUT || type == OUTPUT || type == HEREDOC
		|| type == APPEND || type == SPACES || type == END)
		return (1);
	return (0);
}

int	is_operator(char *str, int i)
{
	t_token_type	type;

	type = identify_type(str, i);
	if (type == PIPE || type == INPUT || type == OUTPUT || type == HEREDOC
		|| type == APPEND)
		return (1);
	return (0);
}

char	*allocate_word(t_shell *shell , char *r_line, int *i)
{
	int		temp_i;
	char	*cmd;
	char	quote;

	temp_i = *i;
	while (r_line[temp_i] && !is_separator(r_line, temp_i))
	{
		if (r_line[temp_i] == '"' || r_line[temp_i] == '\'')
		{
			quote = r_line[temp_i];
			temp_i++;
			while (r_line[temp_i] && r_line[temp_i] != quote)
				temp_i++;
			if (r_line[temp_i] == quote)
				temp_i++;
		}
		else
			temp_i++;
	}
	cmd = gc_malloc(&shell->gc, temp_i - *i + 1);
	return (cmd);
}
