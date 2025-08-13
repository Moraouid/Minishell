/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 04:53:27 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/08/13 12:13:34 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_token(t_token **c_line, t_token *new)
{
	t_token	*last;

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

t_token	*creat_node_cmd(t_shell *shell, char *value, int type)
{
	t_token	*t_cmd;

	t_cmd = gc_malloc(&shell->gc, sizeof(t_token));
	t_cmd->f_empty = 0;
	t_cmd->value = value;
	t_cmd->type = type;
	t_cmd->next = NULL;
	return (t_cmd);
}

int	count_cmd(t_token **token)
{
	int		count;
	t_token	*cur;

	count = 0;
	cur = *token;
	while (cur && cur->type != PIPE)
	{
		if (cur->type == WORD && cur->value)
			count++;
		cur = cur->next;
	}
	return (count);
}

int	isredirction(t_token *token)
{
	if (token->type == INPUT || token->type == OUTPUT || token->type == APPEND
		|| token->type == HEREDOC)
		return (1);
	return (0);
}

void	add_back_cmd(t_command **cmd, t_command *n_cmd)
{
	t_command	*tmp;

	if (!*cmd)
	{
		*cmd = n_cmd;
		return ;
	}
	tmp = *cmd;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = n_cmd;
}
