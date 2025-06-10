/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:26:17 by zatais            #+#    #+#             */
/*   Updated: 2025/06/10 22:52:05 by zatais           ###   ########.fr       */
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

/*void	add_token(t_token **c_line, t_token *new)
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
*/
/*t_token	*creat_node_cmd(char *value, t_type type)
{
	t_token	*t_cmd;
	int		i;
	int		j;
	char	*cmd;
	t_token	*n_token;
	t_token	*print_tmp;

	t_cmd = malloc(sizeof(t_token));
	if (!t_cmd)
		return (NULL);
	t_cmd->cmd = value;
	t_cmd->type = type;
	t_cmd->next = NULL;
	t_cmd->prev = NULL;
	return (t_cmd);
}*/
/*
void	command_line(t_shell *shell)
{
	i = 0;
	while(shell->r_line[i])
	{
		while(shell->r_line[i] == ' ')
			i++;
		if(shell->r_line[i] == '|')
		{
			n_token = creat_node_cmd(ft_strdup("|"), PIPE);
			add_token(&shell->token, n_token);
			i++;
		}
		else if(shell->r_line[i] == '>')
		{
			if(shell->r_line[i + 1] == '>')
			{
				n_token = creat_node_cmd(ft_strdup(">>"), APPEND);
				add_token(&shell->token, n_token);
				i++;
			}
			else
			{
				n_token = creat_node_cmd(ft_strdup(">"), RED_OUT);
				add_token(&shell->token, n_token);
			}
		}
		else if(shell->r_line[i] == '<')
		{
			if(shell->r_line[i + 1] == '<')
			{
				n_token = creat_node_cmd(ft_strdup("<<"), HERDOC);
				add_token(&shell->token, n_token);
				i++;
			}
			else
			{
				n_token = creat_node_cmd(ft_strdup("<"), RED_IN);
				add_token(&shell->token, n_token);
			}
		}
		else
		{
			j = 0;
			while(shell->r_line[i + j] && shell->r_line[i + j] != ' ')
				j++;
			cmd = malloc(j + 1);
			if (!cmd)
				return ;
			j = 0;
			while(shell->r_line[i] && shell->r_line[i] != ' ')
				cmd[j++] = shell->r_line[i++];
			cmd[j] = '\0';
			n_token = creat_node_cmd(cmd, WORD);
			add_token(&shell->token, n_token);
		}
		i++;
	}
	print_tmp = shell->token;
	while(print_tmp != NULL)
	{
		printf("%s\n", print_tmp->cmd);
		if (print_tmp->type == PIPE)
			printf("Type: PIPE\n");
		else if (print_tmp->type == RED_IN)
			printf("Type: RED_IN\n");
		else if (print_tmp->type == RED_OUT)
			printf("Type: RED_OUT\n");
		else if (print_tmp->type == HERDOC)
			printf("Type: HERDOC\n");
		else if (print_tmp->type == APPEND)
			printf("Type: APPEND\n");
		else
			printf("Type: WORD\n");
		printf("------------\n");
		print_tmp = print_tmp->next;
	}
}
*/

int is_space(char c)
{
  return ((c >= 0 && c <= 13) || c == 32);
}

t_token_type	identify_separator(char *str, int i)
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
	return (0);
}

int	update_quote_status(int status, char c)
{
	if (c == '\'' && status == DEFAULT)
		return (SQUOTE);
	if (c == '\"' && status == DEFAULT)
		return (DQUOTE);
	if (c == '\'' && status == SQUOTE)
		return (DEFAULT);
	if (c == '\"' && status == DQUOTE)
		return (DEFAULT);
	return (status);
}

void	add_token(t_shell *shell, t_token_type type, char *value)
{
	t_token	*new_token;
	t_token	*current;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->value = value;
	new_token->type = type;
	new_token->next = NULL;
	if (!shell->tokens)
	{
		shell->tokens = new_token;
		return ;
	}
	current = shell->tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

char	*ft_substr2(char *str, int start, int end)
{
	int		len;
	char	*res;
	int		i;

	len = end - start;
	if (len <= 0)
		return (NULL);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = -1;
	while (++i < len)
		res[i] = str[start + i];
	res[len] = '\0';
	return (res);
}

int save_word_token(t_shell *shell, char *str, int start, int end)
{
	char	*value;

	value = ft_substr2(str, start, end);
  if (!value)
    return(0);
	return (add_token(shell, WORD, value), 1);
}

int	save_operator_token(t_shell *shell, char *str, int index,
		t_token_type type)
{
	char	*value;

	if (type == HEREDOC || type == APPEND)
		value = ft_substr2(str, index, index + 2);
	else
		value = ft_substr2(str, index, index + 1);
  if (!value)
    return (0);
  return (add_token(shell, type, value), 1);
}

int	process_character(t_shell *shell, char *str, int *index, int token_start)
{
	t_token_type	type;

	type = identify_separator(str, *index);
	if (type && *index != token_start)
		if (!save_word_token(shell, str, token_start, *index))
      return(-1);
	if (type == PIPE || type == INPUT || type == OUTPUT || type == HEREDOC
		|| type == APPEND)
	{
		if(!save_operator_token(shell, str, *index, type))
      return (-1);
		if (type == HEREDOC || type == APPEND)
			return (*index += 1, *index + 1);
	}
	if (type)
		return (*index + 1);
	return (token_start);
}

void	print_error(char *msg1, char *msg2, int specific)
{
	if (specific)
		printf("Error: %s '%s'\n", msg1, msg2);
	else
		printf("Error: %s %s\n", msg1, msg2);
}

void	handle_quote_error(int status)
{
	if (status == SQUOTE)
		print_error("unexpected EOF while looking for matching", "\'", 1);
	else if (status == DQUOTE)
		print_error("unexpected EOF while looking for matching", "\"", 1);
	print_error("syntax error", "unexpected end of file", 0);
}

int	tokenize_input(t_shell *shell, char *input)
{
	int	i;
	int	token_start;
	int	status;
	int	length;

	i = -1;
	token_start = 0;
	status = DEFAULT;
	length = ft_strlen(input);
	while (++i <= length)
	{
    //check if you are inside quotes 
		status = update_quote_status(status, input[i]);
    // only enter if you are outside quotes 
		if (status == DEFAULT)
			token_start = process_character(shell, input, &i, token_start); // check if you are in a separator "| ,> ,>> ,< ,<< ,space ,'\0' " start copying from the first char of the the word that start point to then move the start to the next word
    // example : hello>world\0
    //           ^    ^^     ^→sep →start copying from start index 
    //                 →start point here now
    //        start  sep
    //           i→→→→ start copying frome the start and mov start to the next word 
      if (token_start == -1)
        return(0);
	}
	if (status != DEFAULT)
		return (handle_quote_error(status), 0);
	return (1);
}

void	print_tokens(t_shell *shell)
{
	t_token	*current;
	char	*type_str;
	char	*val;
	char	display[256];
	int		pos;

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
		val = current->value;
		pos = 0;
		while (*val)
		{
			if (*val == '\"')
			{
				display[pos] = '\\';
				pos++;
				display[pos] = '\"';
			}
			else if (*val == '\'')
			{
				display[pos] = '\\';
				pos++;
				display[pos] = '\'';
			}
			else
			{
				display[pos] = *val;
			}
			pos++;
			val++;
		}
		display[pos] = '\0';
		printf("[%-6s] = '%s'\n", type_str, display);
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
	if (!tokenize_input(shell, shell->r_line))
		free_tokens(shell);
	print_tokens(shell);
	// command_line(shell);
	// command_execution(read);
}
