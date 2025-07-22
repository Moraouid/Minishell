/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 04:53:27 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/07/18 23:01:10 by sel-abbo         ###   ########.fr       */
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


