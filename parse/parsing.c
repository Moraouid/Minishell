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
int	parsing_command(t_shell *shell)
{
	if (!tokeniziation(shell))
		return (0);
	if (!check_syntax_error(shell, shell->tokens))
		return (0);
	if (!heredoc(shell))
		return (0);
	expansions(shell);
    print_tokens(shell);
	remove_quotes(shell);
    remove_expand_quotes(shell->tokens, shell->r_str, &shell->gc);
	creat_command(shell);
	return (1);
}
