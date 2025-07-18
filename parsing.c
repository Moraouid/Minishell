/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:26:17 by zatais            #+#    #+#             */
/*   Updated: 2025/07/18 23:18:09 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *msg1, char *msg2, int specific)
{
	if (specific)
		printf("Error: %s '%s'\n", msg1, msg2);
	else
		printf("Error: %s %s\n", msg1, msg2);
}

void	handle_quote_error(t_token_status status)
{
	if (status == SQUOTE)
		print_error("unexpected EOF while looking for matching", "'", 1);
	else if (status == DQUOTE)
		print_error("unexpected EOF while looking for matching", "\"", 1);
}

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
	if (type == 0)
		return "REDIR_IN";
	else if (type == 1)
		return "REDIR_OUT";
	else if (type == 2)
		return "APPEND";
	else if (type == 3)
		return "HEREDOC";
	return "UNKNOWN";
}


#include <stdio.h>

void	print_commands(t_command *cmd_list)
{
	int i = 0;
	while (cmd_list)
	{
		printf("=== Command #%d ===\n", i + 1);

		// Print arguments
		printf("Arguments: ");
		if (cmd_list->args)
		{
			for (int j = 0; cmd_list->args[j]; j++)
				printf("\"%s\" ", cmd_list->args[j]);
		}
		else
			printf("(none)");
		printf("\n");

		// Print redirections
		t_redir *r = cmd_list->redirs;
		if (!r)
			printf("Redirections: (none)\n");
		else
		{
			printf("Redirections:\n");
			while (r)
			{
				printf("  - type: %s\n", get_redir_type_string(r->type));
				printf("    target: %s\n", r->target ? r->target : "(null)");
				printf("    h_filename: %s\n", r->h_filename ? r->h_filename : "(null)");
				r = r->next;
			}
		}

		printf("\n");
		cmd_list = cmd_list->next;
		i++;
	}
}



void	parsing_command(t_shell *shell)
{
	tokeniziation(shell); 
	// expansions(shell);
	print_tokens(shell);
	creat_command(shell);
	printf("\nCommands:\n-----------------\n");
	print_commands(shell->cmd);
	
}
