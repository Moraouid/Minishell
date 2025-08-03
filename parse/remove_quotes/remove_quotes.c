/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 11:23:08 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/08/03 17:07:40 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_len_char(t_quotes *flag, char *value, char *r_str)
{
	if (value[flag->i] == '\'' && !flag->dq && !flag->rq)
	{
		flag->sq = !flag->sq;
		flag->i++;
	}
	else if (value[flag->i] == '"' && !flag->sq && !flag->rq)
	{
		flag->dq = !flag->dq;
		flag->i++;
	}
	else if (!ft_strncmp(&value[flag->i], r_str, 9) && !flag->dq && !flag->sq)
	{
		flag->len++;
		flag->rq = !flag->rq;
		flag->i++;
	}
	else
	{
		flag->len++;
		flag->i++;
	}
}

int	len_whitout_quotes(t_gc_node **gc, char *value, char *r_str)
{
	t_quotes	*flag;

	flag = gc_malloc(gc, sizeof(t_quotes));
	init_flag(flag);
	while (value && value[flag->i])
		handle_len_char(flag, value, r_str);
	return (flag->len);
}

char	*remove_quotes_helper(t_shell *shell, char *value, t_quotes *flag,
		char *r_str)
{
	char	*res;

	res = gc_malloc(&shell->gc, flag->len + 1);
	while (value[flag->i])
	{
		if (value[flag->i] == '\'' && !flag->dq && !flag->rq)
		{
			flag->sq = !flag->sq;
			flag->i++;
		}
		else if (value[flag->i] == '"' && !flag->sq && !flag->rq)
		{
			flag->dq = !flag->dq;
			flag->i++;
		}
		else if (!ft_strncmp(&value[flag->i], r_str, 9) && !flag->dq
			&& !flag->sq)
		{
			value[flag->j++] = value[flag->i++];
			flag->rq = !flag->rq;
		}
		else
			value[flag->j++] = value[flag->i++];
	}
	return (value);
}

void	remove_quotes(t_shell *shell)
{
	char		*value;
	t_token		*current;
	t_quotes	*flag;

	flag = gc_malloc(&shell->gc, sizeof(t_quotes));
	current = shell->tokens;
	init_flag(flag);
	while (current)
	{
		flag->i = 0;
		flag->j = 0;
		flag->len = len_whitout_quotes(&shell->gc, current->value,
				shell->r_str);
		value = remove_quotes_helper(shell, current->value, flag, shell->r_str);
		value[flag->j] = '\0';
		current->value = value;
		current = current->next;
	}
}
