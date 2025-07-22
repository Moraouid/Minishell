/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 03:33:38 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/07/21 03:06:45 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(t_errno errno, char *str)
{
	if (errno == ERRNO_DQ || errno == ERRNO_SQ)
		write(2, "Niggshell: unexpected EOF while loking for matching ", 52);
	else if (errno == ERRNO_RD || errno == ERRNO_P || errno == ERRNO_A)
		write(2, "Niggshell: syntax error near unexpected token ", 46);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

int	check_quots(char *r_line)
{
	t_token_status	status;
	int				i;

	status = DEFAULT;
	i = 0;
	while (r_line[i])
		status = update_quote_status(status, r_line[i++]);
	if (status != DEFAULT)
	{
		if (status == DQUOTE)
			print_error(ERRNO_DQ, "\"");
		else if (status == SQUOTE)
			print_error(ERRNO_SQ, "'");
		return (0);
	}
	return (1);
}

int	check_pipe(t_token *token)
{
	t_token	*cur;

	cur = token;
	if (token->type == PIPE)
	{
		if (token->next && token->next->type == PIPE)
			print_error(ERRNO_P, "`||'");
		else
			print_error(ERRNO_P, "`|'");
		return (0);
	}
	while (cur)
	{
		if (cur->type == PIPE && (cur->next == NULL || cur->next->type == PIPE))
		{
			if (cur->next && cur->next->type == PIPE)
				print_error(ERRNO_P, "`||'");
			else
				print_error(ERRNO_P, "`|'");
			return (0);
		}
		cur = cur->next;
	}
	return (1);
}

int	check_redir(t_token *token)
{
	t_token	*cur;

	cur = token;
	while (cur)
	{
		if (isredirction(cur) && (cur->next == NULL || isredirction(cur->next)))
		{
			if (cur->next)
				print_error(ERRNO_RD, cur->next->value);
			else
				print_error(ERRNO_RD, "'newline'");
			return (0);
		}
		cur = cur->next;
	}
	return (1);
}

int	check_syntax_error(t_token *token)
{
	if (!check_pipe(token))
		return (0);
	if (!check_redir(token))
		return (0);
	return (1);
}
