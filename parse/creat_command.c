/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:51:17 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/08/03 19:09:31 by sel-abbo         ###   ########.fr       */
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

void	fill_args_and_redirs(t_shell *shell, char **args, t_redir **redir)
{
	int		i;
	t_redir	*n_redir;

	i = 0;
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
			add_back_redir(redir, n_redir);
			shell->tokens = shell->tokens->next->next;
		}
	}
	args[i] = NULL;
}

void	creat_command(t_shell *shell)
{
	int			count;
	char		**args;
	t_redir		*redir;
	t_command	*n_cmd;

	redir = NULL;
	shell->cmd = NULL;
	while (shell->tokens)
	{
		count = count_word_list(&shell->tokens);
		args = gc_malloc(&shell->gc, (count + 1) * sizeof(char *));
		fill_args_and_redirs(shell, args, &redir);
		n_cmd = creat_cmd(shell, args, redir);
		add_back_cmd(&shell->cmd, n_cmd);
		redir = NULL;
		if (shell->tokens && shell->tokens->type == PIPE)
			shell->tokens = shell->tokens->next;
	}
}
