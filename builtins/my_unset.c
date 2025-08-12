/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:15:10 by zatais            #+#    #+#             */
/*   Updated: 2025/08/11 22:00:46 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_and_update(t_env **prev, t_env **current, t_env **env,
		t_gc_node **gc)
{
	t_env	*temp;

	temp = *current;
	if (!*prev)
	{
		*env = temp->next;
		*current = *env;
	}
	else
	{
		(*prev)->next = temp->next;
		*current = (*prev)->next;
	}
	gc_remove(gc, temp->value);
	gc_remove(gc, temp);
}

int	my_unset(t_env **env, char **args, t_gc_node **gc)
{
	int		i;
	t_env	*prev;
	t_env	*current;

	if (!args || !*args)
		return (0);
	i = -1;
	while (args[++i])
	{
		current = *env;
		prev = NULL;
		while (current)
		{
			if (!ft_strncmp(current->value, args[i], ft_strlen(args[i]))
				&& (current->value[ft_strlen(args[i])] == '='
					|| current->value[ft_strlen(args[i])] == '\0'))
			{
				free_and_update(&prev, &current, env, gc);
				break ;
			}
			else
				(1) && (prev = current, current = current->next);
		}
	}
	return (0);
}
