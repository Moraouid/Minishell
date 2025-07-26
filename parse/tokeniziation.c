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

#include "../includes/minishell.h"

t_token	*handle_operator(t_shell *shell, int *i, int type)
{
	t_token	*n_token;

	n_token = NULL;
	if (type == PIPE)
		n_token = creat_node_cmd(shell, ft_strdup("|", &shell->gc), PIPE);
	else if (type == INPUT)
		n_token = creat_node_cmd(shell, ft_strdup("<", &shell->gc), INPUT);
	else if (type == OUTPUT)
		n_token = creat_node_cmd(shell, ft_strdup(">", &shell->gc), OUTPUT);
	else if (type == HEREDOC)
		n_token = creat_node_cmd(shell, ft_strdup("<<", &shell->gc), HEREDOC);
	else if (type == APPEND)
		n_token = creat_node_cmd(shell, ft_strdup(">>", &shell->gc), APPEND);
	if (type == HEREDOC || type == APPEND)
		*i += 2;
	else
		*i += 1;
	return (n_token);
}

void	fill_word(char *r_line, int *i, char *cmd, int *j)
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
}

t_token	*handle_word(t_shell *shell, char *r_line, int *i)
{
	int		j;
	char	*cmd;

	j = 0;
	cmd = allocate_word(shell, r_line, i);
	j = 0;
	while (r_line[*i] && !is_separator(r_line, *i))
		fill_word(r_line, i, cmd, &j);
	cmd[j] = '\0';
	return (creat_node_cmd(shell, cmd, WORD));
}

t_token	*handle_word_token(t_shell *shell, int *i)
{
	t_token	*n_token;

	n_token = handle_word(shell, shell->r_line, i);
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
			n_token = handle_operator(shell, &i, type);
		else
			n_token = handle_word_token(shell, &i);
		add_token(&shell->tokens, n_token);
	}
	return (1);
}
