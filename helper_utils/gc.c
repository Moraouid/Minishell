/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 10:24:52 by zatais            #+#    #+#             */
/*   Updated: 2025/08/12 12:12:45 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	gc_clean(t_gc_node **gc)
{
	t_gc_node	*current;
	t_gc_node	*next;

	current = *gc;
	while (current)
	{
		next = current->next;
		free(current->ptr);
		free(current);
		current = next;
	}
	*gc = NULL;
}

void	gc_add(t_gc_node **gc, void *ptr)
{
	t_gc_node	*node;
	t_shell		*shell;

	shell = get_shell(NULL);
	node = malloc(sizeof(t_gc_node));
	if (!node)
	{
		write(2, "Niggshell: gc_add malloc failed\n", 31);
		gc_clean(&shell->gc);
		gc_clean(&shell->env_gc);
		exit(1);
	}
	node->ptr = ptr;
	node->next = *gc;
	*gc = node;
}

void	gc_remove(t_gc_node **gc, void *ptr)
{
	t_gc_node	*current;
	t_gc_node	*prev;

	current = *gc;
	prev = NULL;
	while (current)
	{
		if (current->ptr == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				*gc = current->next;
			free(current->ptr);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	*gc_malloc(t_gc_node **gc, size_t size)
{
	void	*ptr;
	t_shell	*shell;

	shell = get_shell(NULL);
	ptr = malloc(size);
	if (!ptr)
	{
		write(2, "Niggshell: malloc failed\n", 25);
		gc_clean(&shell->gc);
		gc_clean(&shell->env_gc);
		exit(1);
	}
	gc_add(gc, ptr);
	return (ptr);
}
