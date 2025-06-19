/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:26:17 by zatais            #+#    #+#             */
/*   Updated: 2025/06/17 19:11:14 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_redir		*creat_node_red(char *value, char *target, int	type)
// {
// 	t_redir	*t_red;

// 	t_red = malloc(sizeof(t_red));
// 	if(!t_red)
// 		return(NULL);
// 	t_red->content = value;
// 	t_red->target = target;
// 	t_red->type = type;
// 	t_red->next = NULL;
// 	return (t_red);
// }

void	print_error(char *msg1, char *msg2, int specific)
{
	if (specific)
		printf("Error: %s '%s'\n", msg1, msg2);
	else
		printf("Error: %s %s\n", msg1, msg2);
}

void	handle_quote_error(int type)
{
	if (type == SQUOTE)
		print_error("unexpected EOF while looking for matching", "\'", 1);
	else if (type == DQUOTE)
		print_error("unexpected EOF while looking for matching", "\"", 1);
	print_error("syntax error", "unexpected end of file", 0);
}

void	add_token(t_token **c_line, t_token *new)
{
	t_token	*last;

	if (!new)
		return ;
	if (*c_line == NULL)
	{
		*c_line = new;
		return ;
	}
	last = *c_line;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	new->prev = last;
}
t_token	*creat_node_cmd(char *value, int type)
{
	t_token	*t_cmd;

	t_cmd = malloc(sizeof(t_token));
	if (!t_cmd)
		return (NULL);
	t_cmd->value = value;
	t_cmd->type = type;
	t_cmd->next = NULL;
	t_cmd->prev = NULL;
	return (t_cmd);
}

int is_space(char c)
{
  return ((c >= 0 && c <= 13) || c == 32);
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
	if(str[i] == '\"')
		return (DQUOTE);
	if(str[i] == '\'')
		return (SQUOTE);
	return (WORD);
}

static t_token *handle_operator(char *r_line, int *i, int type)
{
	t_token *n_token;

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

static char *extract_quoted_content(char *r_line, int *i, int type, char quote)
{
	int j = 0;
	char *cmd;

	(*i)++;
	while (r_line[*i + j] && r_line[*i + j] != quote)
		j++;
	if (!r_line[*i + j])
	{
		handle_quote_error(type);
		return (NULL);
	}
	cmd = malloc(j + 1);
	if (!cmd)
		return (NULL);
	j = 0;
	while (r_line[*i] && r_line[*i] != quote)
		cmd[j++] = r_line[(*i)++];
	cmd[j] = '\0';
	(*i)++;
	return (cmd);
}

static t_token *handle_quoted_token(char *r_line, int *i, int type)
{
	char quote;
	char *cmd;
	
	quote = r_line[*i];
	cmd = extract_quoted_content(r_line, i, type, quote);
	if (!cmd)
		return (NULL);
	return (creat_node_cmd(cmd, type));
}

static char *extract_complex_word(char *r_line, int *i)
{
	int j = 0;
	int k;
	char *cmd;
	char quote;
	int type;

	while (r_line[*i + j] &&
		!is_space(r_line[*i + j]) &&
		(identify_type(r_line, *i + j) == WORD || 
		identify_type(r_line, *i + j) == DQUOTE || 
		identify_type(r_line, *i + j) == SQUOTE))
		j++;
	cmd = malloc(j + 1);
	if (!cmd)
		return (NULL);
	return (cmd);
}

static int fill_complex_word(char *r_line, int *i, char *cmd, int *j)
{
	int k;
	char quote;
	int type;

	if (identify_type(r_line, *i) == DQUOTE || identify_type(r_line, *i) == SQUOTE)
	{
		type = identify_type(r_line, *i);
		quote = r_line[(*i)++];
		k = 0;
		while (r_line[*i + k] && r_line[*i + k] != quote)
			k++;
		if (!r_line[*i + k])
		{
			handle_quote_error(type);
			return (0);
		}
		while (k--)
			cmd[(*j)++] = r_line[(*i)++];
		(*i)++;
	}
	else
		cmd[(*j)++] = r_line[(*i)++];
	return (1);
}

static t_token *handle_complex_word(char *r_line, int *i)
{
	int j;
	char *cmd;
	
	j = 0;
	cmd = extract_complex_word(r_line, i);
	if (!cmd)
		return (NULL);
	j = 0;
	while (r_line[*i] &&
		!is_space(r_line[*i]) &&
		(identify_type(r_line, *i) == WORD || 
		identify_type(r_line, *i) == DQUOTE || 
		identify_type(r_line, *i) == SQUOTE))
	{
		if (!fill_complex_word(r_line, i, cmd, &j))
		{
			free(cmd);
			return (NULL);
		}
	}
	cmd[j] = '\0';
	return (creat_node_cmd(cmd, WORD));
}

void command_line(t_shell *shell)
{
	int i = 0;
	int type;
	t_token *n_token;

	while (shell->r_line[i])
	{
		while (shell->r_line[i] && is_space(shell->r_line[i]))
			i++;
		if (!shell->r_line[i])
			break;
		type = identify_type(shell->r_line, i);
		if (type == PIPE || type == INPUT || type == OUTPUT || type == HEREDOC || type == APPEND)
			n_token = handle_operator(shell->r_line, &i, type);
		else if (type == DQUOTE || type == SQUOTE)
			n_token = handle_quoted_token(shell->r_line, &i, type);
		else
			n_token = handle_complex_word(shell->r_line, &i);
		add_token(&shell->tokens, n_token);
	}
}

void	print_tokens(t_shell *shell)
{
	t_token	*current;
	char	*type_str;

	current = shell->tokens;
	printf("\nTokens:\n-----------------\n");
	while (current)
	{
		if (current->type == WORD)
			type_str = "WORD";
		else if (current->type == PIPE)
			type_str = "PIPE";
		else if (current->type == INPUT)
			type_str = "INPUT";
		else if (current->type == OUTPUT)
			type_str = "OUTPUT";
		else if (current->type == HEREDOC)
			type_str = "HEREDOC";
		else if (current->type == APPEND)
			type_str = "APPEND";
		else if (current->type == SPACES)
			type_str = "SPACES";
		else if (current->type == DQUOTE)
			type_str = "DQUOTE";
		else if (current->type == SQUOTE)
			type_str = "SQUOTE";
		printf("[%-6s] = %s\n", type_str, current->value);
		current = current->next;
	}
	printf("-----------------\n");
}

void	free_tokens(t_shell *shell)
{
	t_token	*current;
	t_token	*next;

	current = shell->tokens;
	while (current)
	{
		next = current->next;
		free(current->value);// strdup
		free(current);
		current = next;
	}
	shell->tokens = NULL;
}
//	this function for parssing

void	parsing_command(t_shell *shell)
{
	// if (!tokenize_input(shell, shell->r_line))
	// 	free_tokens(shell);
	command_line(shell);
	print_tokens(shell);
	// command_execution(read);
}
