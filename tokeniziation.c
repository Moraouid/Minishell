/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniziation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 03:57:54 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/07/20 06:29:32 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*handle_operator(int *i, int type)
{
	t_token	*n_token;

	n_token = NULL;
	if (type == PIPE)
		n_token = creat_node_cmd(ft_strdup("|"), PIPE);
	else if (type == INPUT)
		n_token = creat_node_cmd(ft_strdup("<"), INPUT);
	else if (type == OUTPUT)
		n_token = creat_node_cmd(ft_strdup(">"), OUTPUT);
	else if (type == HEREDOC)
		n_token = creat_node_cmd(ft_strdup("<<"), HEREDOC);
	else if (type == APPEND)
		n_token = creat_node_cmd(ft_strdup(">>"), APPEND);
	if (type == HEREDOC || type == APPEND)
		*i += 2;
	else
		*i += 1;
	return (n_token);
}

int	fill_word(char *r_line, int *i, char *cmd, int *j)
{
	int		k;
	char	quote;

	if (r_line[*i] == '"' || r_line[*i] == '\'')
	{
		quote = r_line[*i];
		cmd[(*j)++] = r_line[(*i)++];
		k = 0;
		while (r_line[*i + k] && r_line[*i + k] != quote)
			k++;
		while (k--)
			cmd[(*j)++] = r_line[(*i)++];
		cmd[(*j)++] = r_line[(*i)++];
	}
	else
		cmd[(*j)++] = r_line[(*i)++];
	return (1);
}

t_token	*handle_word(char *r_line, int *i)
{
	int		j;
	char	*cmd;

	j = 0;
	cmd = allocate_word(r_line, i);
	if (!cmd)
		return (NULL);
	j = 0;
	while (r_line[*i] && !is_separator(r_line, *i))
	{
		if (!fill_word(r_line, i, cmd, &j))
		{
			free(cmd);
			return (NULL);
		}
	}
	cmd[j] = '\0';
	return (creat_node_cmd(cmd, WORD));
}

t_token	*handle_word_token(t_shell *shell, int *i)
{
	t_token	*n_token;

	n_token = handle_word(shell->r_line, i);
	if (!n_token)
		return (NULL);
	return (n_token);
}


int	tokeniziation(t_shell *shell)
{
	int		i;
	int		type;
	t_token	*n_token;

	if (!check_quots(shell->r_line))
		return (0);
	i = 0;
	while (shell->r_line[i])
	{
		while (shell->r_line[i] && is_space(shell->r_line[i]))
			i++;
		if (shell->r_line[i] == '&')
		{
			if (shell->r_line[i + 1] == '&')
				print_error(ERRNO_A, "'&&'");
			else
				print_error(ERRNO_A, "'&'");
			return (0);
		}
		if (!shell->r_line[i])
			break ;
		type = identify_type(shell->r_line, i);
		if (is_operator(shell->r_line, i))
			n_token = handle_operator(&i, type);
		else
			n_token = handle_word_token(shell, &i);
		add_token(&shell->tokens, n_token);
	}
	return (1);
}
