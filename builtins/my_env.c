/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:14:59 by zatais            #+#    #+#             */
/*   Updated: 2025/08/10 12:18:09 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_var_exist(t_env *env, char *var)
{
	while (env)
	{
		if (!ft_strncmp(env->value, var, 5))
			return (1);
		env = env->next;
	}
	return (0);
}

int	my_env(t_env *env)
{
	t_env	*tmp;

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
	printf("%s\n", tmp->value);
	return (0);
}
