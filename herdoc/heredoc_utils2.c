/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote_delimiter.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 10:14:17 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/08/09 20:28:08 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	len_of_allocate(char *str)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while (str[i++] != quote)
				count++;
		}
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

char	*remove_quote_delimiter(t_gc_node **gc, char *str)
{
	int		i;
	int		j;
	int		len;
	char	*res;
	char	quote;

	i = 0;
	j = 0;
	len = len_of_allocate(str);
	res = gc_malloc(gc, len + 1);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while (str[i] != quote)
				res[j++] = str[i++];
			i++;
		}
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}
