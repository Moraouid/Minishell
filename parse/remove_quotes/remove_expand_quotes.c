/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_expand_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 11:27:35 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/08/03 17:08:36 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	len_allocate(char *str, char *r_str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (!ft_strncmp(&str[i], r_str, 9))
			i += 9;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

char	*remove_rstr_from_value(char *str, char *r_str, t_gc_node **gc)
{
	char	*res;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = len_allocate(str, r_str);
	res = gc_malloc(gc, len + 1);
	while (str[i])
	{
		if (!ft_strncmp(&str[i], r_str, 9))
			i += 9;
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	if (*res == '\0')
		return (NULL);
	return (res);
}

void	remove_expand_quotes(t_token *tokens, char *r_str, t_gc_node **gc)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (ft_strlen(current->value) != 0)
			current->value = remove_rstr_from_value(current->value, r_str, gc);
		current = current->next;
	}
}
