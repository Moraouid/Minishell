/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:51:17 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/07/19 00:14:37 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir *creat_node_redirction(t_token_type type, char *target)
{
	t_redir *redirction;
	
	redirction = malloc(sizeof(t_redir));
	if(!redirction)
		return (NULL);
	memset(redirction, 0, sizeof(t_redir));
	redirction->type = type;
	if (type == HEREDOC)
		redirction->h_filename = target;
	else
		redirction->target = target;
	redirction->next = NULL;
	return (redirction);
}

void add_back_redir(t_redir **redir, t_redir *new_redir)
{
  t_redir *temp;

  if (!redir || !new_redir)
	return;
  if (!*redir)
  {
	*redir = new_redir;
	return;
  }
  temp = *redir;
  while (temp->next)
	temp = temp->next;
  temp->next = new_redir;
}

t_command *creat_cmd(char **args, t_redir *redirs)
{
	t_command *cmd;
	
	cmd = malloc(sizeof(t_command));
	if(!cmd)
		return NULL;
	cmd->args = args;
	cmd->redirs = redirs;
	cmd->next = NULL;
	return (cmd);
}

void add_back_cmd(t_command **cmd, t_command *n_cmd)
{
	t_command *tmp;

	if(!*cmd)
	{
		*cmd = n_cmd;
		return;
	}
	tmp = *cmd;
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = n_cmd;
}

int isredirction(t_token *token)
{
  if(token->type == INPUT || token->type == OUTPUT || token->type == APPEND || token->type == HEREDOC)
    return (1);
  return (0);
}

void creat_command(t_shell *shell)
{
	t_redir *redir;
	t_redir *n_redir;
	t_command *n_cmd;
	t_token *tmp;
	char **args = malloc(10000);
	int i;

	shell->cmd = NULL;
	redir = NULL;
	while(shell->tokens)
	{
		n_cmd = NULL;
		while(shell->tokens && shell->tokens->type != PIPE)
		{
			i = 0;
    		while (shell->tokens && shell->tokens->type == WORD)
    		{
				args[i] = ft_strdup(shell->tokens->value);
				shell->tokens = shell->tokens->next;
				tmp = shell->tokens;
				i++;
    		}
    		while(shell->tokens && isredirction(shell->tokens))
    		{
				n_redir = creat_node_redirction(shell->tokens->type, shell->tokens->next->value);
    			add_back_redir(&redir, n_redir);
				shell->tokens = shell->tokens->next->next;
				// tmp = shell->tokens;
    		}
    		// shell->tokens = tmp;cd
    	}
		n_cmd = creat_cmd(args, redir);
		add_back_cmd(&shell->cmd, n_cmd);
		redir = NULL;
		if (shell->tokens && shell->tokens->type == PIPE)
		{
			shell->tokens = shell->tokens->next;
			tmp = shell->tokens;
		}
    	shell->tokens = tmp;
  }
}
