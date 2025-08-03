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

#include "../includes/minishell.h"

t_redir	*creat_node_redirction(t_shell *shell, t_token_type type, t_token *next)
{
	t_redir	*redirction;

	redirction = gc_malloc(&shell->gc, sizeof(t_redir));
	memset(redirction, 0, sizeof(t_redir));
	redirction->type = type;
	if (next->type == AMBGUS)
		redirction->f_ambiguous = 1;
	else
		redirction->f_ambiguous = 0;
	if (type == HEREDOC)
		redirction->h_filename = next->value;
	else
		redirction->target = next->value;
	redirction->next = NULL;
	return (redirction);
}

void	add_back_redir(t_redir **redir, t_redir *new_redir)
{
	t_redir	*temp;

	if (!*redir)
	{
		*redir = new_redir;
		return ;
	}
	temp = *redir;
	while (temp->next)
		temp = temp->next;
	temp->next = new_redir;
}

t_command	*creat_cmd(t_shell *shell, char **args, t_redir *redirs)
{
	t_command	*cmd;

	cmd = gc_malloc(&shell->gc, sizeof(t_command));
	cmd->args = args;
	cmd->redirs = redirs;
	cmd->next = NULL;
	return (cmd);
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

int	isredirction(t_token *token)
{
	if (token->type == INPUT || token->type == OUTPUT || token->type == APPEND
		|| token->type == HEREDOC)
		return (1);
	return (0);
}

int	count_word_list(t_token **token)
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

void	creat_command(t_shell *shell)
{
	int			i;
	int			count;
	char		**args;
	t_redir		*redir;
	t_redir		*n_redir;
	t_command	*n_cmd;

	redir = NULL;
	shell->cmd = NULL;
	while (shell->tokens)
	{
		i = 0;
		n_cmd = NULL;
		count = count_word_list(&shell->tokens);
		args = gc_malloc(&shell->gc, (count + 1) * sizeof(char *));
		while (shell->tokens && shell->tokens->type != PIPE)
		{
			while (shell->tokens && (shell->tokens->type == WORD
					|| shell->tokens->type == AMBGUS))
			{
				if (shell->tokens->value)
					args[i++] = ft_strdup(shell->tokens->value, &shell->gc);
				shell->tokens = shell->tokens->next;
			}
			while (shell->tokens && isredirction(shell->tokens))
			{
				n_redir = creat_node_redirction(shell, shell->tokens->type,
						shell->tokens->next);
				add_back_redir(&redir, n_redir);
				shell->tokens = shell->tokens->next->next;
			}
			args[i] = NULL;
		}
		n_cmd = creat_cmd(shell, args, redir);
		add_back_cmd(&shell->cmd, n_cmd);
		redir = NULL;
		if (shell->tokens && shell->tokens->type == PIPE)
			shell->tokens = shell->tokens->next;
	}
}
