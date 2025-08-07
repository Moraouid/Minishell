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

int	parsing_command(t_shell *shell)
{
	if (!tokeniziation(shell))
		return (0);
	if (!check_syntax_error(shell, shell->tokens))
		return (0);
	if (!heredoc(shell))
		return (0);
	expansions(shell);
	remove_quotes(shell);
	remove_expand_quotes(shell->tokens, shell->r_str, &shell->gc);
	creat_command(shell);
	return (1);
}
