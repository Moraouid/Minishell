/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_after_expand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 11:48:40 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/08/11 22:47:51 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_split_result(t_shell *shell, char *value, char **res,
		t_quotes *flag)
{
	while (value && value[flag->i])
	{
		if (value[flag->i] == '"' && !flag->sq && !flag->rq)
			flag->dq = !flag->dq;
		if (value[flag->i] == '\'' && !flag->dq && !flag->rq)
			flag->sq = !flag->sq;
		if (!ft_strncmp(&value[flag->i], shell->r_str, 9) && !flag->dq
			&& !flag->sq)
			flag->rq = !flag->rq;
		if (is_space(value[flag->i]) && flag->rq)
		{
			res[flag->j] = ft_substr(value, flag->start, flag->i - flag->start,
					&shell->gc);
			while (is_space(value[flag->i]))
				flag->i++;
			flag->start = flag->i;
			flag->j++;
		}
		else
			flag->i++;
	}
}

char	**e_split(t_shell *shell, char *value, int count)
{
	char		**res;
	t_quotes	*flag;

	flag = gc_malloc(&shell->gc, sizeof(t_quotes));
	init_flag(flag);
	res = gc_malloc(&shell->gc, (count + 1) * sizeof(char *));
	fill_split_result(shell, value, res, flag);
	if (flag->i > flag->start)
	{
		res[flag->j] = ft_strdup(&value[flag->start], &shell->gc);
		res[flag->j + 1] = NULL;
	}
	else
		res[flag->j] = NULL;
	return (res);
}

void	process_token_split(t_shell *shell, t_token **token, char **split)
{
	int		i;
	t_token	*next;
	t_token	*new_token;

	i = 1;
	next = (*token)->next;
	(*token)->value = split[0];
	while (split[i])
	{
		new_token = creat_node_cmd(shell, split[i], WORD);
		(*token)->next = new_token;
		*token = new_token;
		i++;
	}
	(*token)->next = next;
}

void	split_after_expand(t_shell *shell, t_token **token, char *j_str)
{
	int		count;
	char	**split;

	count = count_for_split(&shell->gc, j_str, shell->r_str);
	split = e_split(shell, j_str, count);
	process_token_split(shell, token, split);
}
