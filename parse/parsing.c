/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:26:17 by zatais            #+#    #+#             */
/*   Updated: 2025/08/03 19:13:03 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/history.h>
#include <stdio.h>

int	is_space(char c)
{
	return ((c >= 0 && c <= 13) || c == 32);
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
		else if (current->type == AMBGUS)
			type_str = "AMBGUS";
		printf("[%-6s] = %s\n", type_str, current->value);
		current = current->next;
	}
	printf("-----------------\n");
}

void	init_cmd(t_command *cmd)
{
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
}

const char	*get_redir_type_string(int type)
{
	if (type == INPUT)
		return ("REDIR_IN");
	else if (type == OUTPUT)
		return ("REDIR_OUT");
	else if (type == APPEND)
		return ("APPEND");
	else if (type == HEREDOC)
		return ("HEREDOC");
	return ("UNKNOWN");
}

void	print_redirs_fancy(t_redir *redir)
{
	while (redir)
	{
		printf("    └─🔁 Redirection\n");
		printf("       ├─ Type      : %s\n",
			get_redir_type_string(redir->type));
		printf("       ├─ Target    : %s\n",
			redir->target ? redir->target : "(null)");
		printf("       └─ HereDoc   : %s\n",
			redir->h_filename ? redir->h_filename : "(null)");
		redir = redir->next;
	}
}

void	print_commands(t_command *cmd)
{
	while (cmd)
	{
		printf("  ├─ Args: ");
		if (cmd->args && cmd->args[0])
		{
			for (int i = 0; cmd->args[i]; i++)
			{
				printf("%s", cmd->args[i]);
				if (cmd->args[i + 1])
					printf(" ");
			}
			printf("\n");
		}
		else
		{
			printf("  ├─ Args   : (null)\n");
		}
		if (cmd->redirs)
		{
			printf("  └─ Redirections:\n");
			print_redirs_fancy(cmd->redirs);
		}
		else
		{
			printf("  └─ Redirections: (none)\n");
		}
		if (cmd->next)
			printf("    ↓\n");
		cmd = cmd->next;
	}
}

int	parsing_command(t_shell *shell)
{
	if (!tokeniziation(shell))
		return (0);
	if (!check_syntax_error(shell, shell->tokens))
		return (0);
	expansions(shell);
	remove_quotes(shell);
	remove_expand_quotes(shell->tokens, shell->r_str, &shell->gc);
	// print_tokens(shell);
	creat_command(shell);
	// printf("\nCommands:\n-----------------\n");
	// print_commands(shell->cmd);
	return (1);
}
