/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:14:59 by zatais            #+#    #+#             */
/*   Updated: 2025/08/17 17:58:05 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	my_env(t_env *env)
{
	t_env	*tmp;

	tmp = NULL;
	while (env)
	{
		if (!ft_strncmp(env->value, "_=", 2))
		{
			tmp = env;
			env = env->next;
			continue ;
		}
		if (ft_strchr(env->value, '='))
		{
			printf("%s\n", env->value);
			env = env->next;
		}
		else
			env = env->next;
	}
	if (tmp)
		printf("%s\n", tmp->value);
	return (0);
}
