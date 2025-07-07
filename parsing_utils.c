/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 04:53:27 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/06/26 19:12:48 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_tokens(t_shell *shell)
{
	t_token	*current;
	t_token	*next;

	current = shell->tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	shell->tokens = NULL;
}

int	check_syntax_error(char *r_line)
{
	int	i;
	t_token_status	status;
	
	i = 0;
	status = DEFAULT;
	while(r_line[i])
		status = update_quote_status(status, r_line[i++]);
	if (status != DEFAULT)
		return (handle_quote_error(SQUOTE), 0);
	if (r_line[0] == '|' || r_line[0] == '>' || r_line[0] == '<')
		return (print_error("syntax error near unexpected token", &r_line[0], 1), 0);
	return (1);
}
