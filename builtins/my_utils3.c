/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 06:22:29 by zatais            #+#    #+#             */
/*   Updated: 2025/08/03 06:22:29 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */ 
#include "../includes/minishell.h"

void	cmd_error2(char *arg)
{
	ft_putstr_fd("Niggshell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	create_new_node(t_env **env, char *arg, t_gc_node **gc)
{
	t_env	*new_node;

	new_node = create_node(arg, gc);
	add_back(env, new_node);
	return (0);
}
