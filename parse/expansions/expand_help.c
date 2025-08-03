/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:42:17 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/08/03 16:45:42 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_flag(t_quotes *flag)
{
	flag->i = 0;
	flag->rq = 0;
	flag->sq = 0;
	flag->dq = 0;
	flag->len = 0;
	flag->start = 0;
}

int	count_for_split(t_gc_node **gc, char *value, char *r_str)
{
	t_quotes	*flag;

	flag = gc_malloc(gc, sizeof(t_quotes));
	init_flag(flag);
	while (value[flag->i])
	{
		if (value[flag->i] == '"' && !flag->sq && !flag->rq)
			flag->dq = !flag->dq;
		if (value[flag->i] == '\'' && !flag->dq && !flag->rq)
			flag->sq = !flag->sq;
		if (!ft_strncmp(&value[flag->i], r_str, 9) && !flag->dq && !flag->sq)
			flag->rq = !flag->rq;
		if (isspace(value[flag->i]) && flag->rq)
		{
			while (isspace(value[flag->i]))
				flag->i++;
			flag->len++;
		}
		else
			flag->i++;
	}
	flag->len++;
	return (flag->len);
}
