/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:26:17 by zatais            #+#    #+#             */
/*   Updated: 2025/07/02 00:41:30 by sel-abbo         ###   ########.fr       */
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
	cmd->prev = NULL;
}

void	creat_command(t_shell *shell)
{
	t_command	*cmd;

	cmd = split_commands(shell->tokens);
	
}


void	parsing_command(t_shell *shell)
{
	tokeniziation(shell); 
	// creat_command(shell);
  // expansions(shell);
	print_tokens(shell);

}
