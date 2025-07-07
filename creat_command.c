/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:51:17 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/07/05 21:51:17 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

t_redir *creat_node_redirction(t_token_type type, char *target, char *content)
{
  t_redir *redirction;

  redirction = malloc(sizeof(t_redir));
  if(!redirction)
    return (NULL);
  redirction->type = type;
  redirction->target = target;
  redirction->content = content;
  redirction->next = NULL;
  return (redirction);
}

t_command	*new_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

t_command	*split_commands(t_token *tokens)
{
  t_token *temp;
  t_command *cmd;
  t_command *n_cmd;

  temp = tokens;
  cmd = new_command();
  while(tokens)
  {
    int i = 0;
    if(tokens->type == INPUT || tokens->type == OUTPUT)
    {
      cmd->redirs = creat_node_redirction(tokens->type, tokens->next->value, NULL);
      tokens = tokens->next->next;
    }
    if(tokens->type == WORD)
    {
      cmd->args[i] = ft_strdup(tokens->value);
      tokens = tokens->next;
      i++;
    }
    if(tokens->type == PIPE)
    {
      n_cmd = new_command();
      add_node_command(cmd, n_cmd);
      tokens = tokens->next;
    }  
  }
  return NULL;
}

