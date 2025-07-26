/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 04:53:27 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/07/26 09:37:55 by zatais           ###   ########.fr       */
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
	t_cmd->value = value;
	t_cmd->type = type;
	t_cmd->next = NULL;
	return (t_cmd);
}

