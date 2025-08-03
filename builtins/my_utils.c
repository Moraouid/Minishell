/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 06:09:55 by zatais            #+#    #+#             */
/*   Updated: 2025/08/03 06:09:55 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_value(t_env *env, char *key)
{
	size_t	key_len;
	char	*val;

	key_len = ft_strlen(key);
	while (env)
	{
		if (!ft_strncmp(env->value, key, key_len) && (env->value[key_len] == '='
				|| env->value[key_len] == '\0'))
		{
			val = ft_strchr(env->value, '=');
			if (val)
				return (val + 1);
		}
		env = env->next;
	}
	return (NULL);
}

size_t	get_len(char *str)
{
	char	*eq;
	size_t	len;

	eq = ft_strchr(str, '=');
	if (eq)
		len = eq - str;
	else
		len = ft_strlen(str);
	return (len);
}

int	compare_env_vars(char *s1, char *s2)
{
	int	len2;
	int	len1;
	int	cmp;
	int	min_len;

	len1 = get_len(s1);
	len2 = get_len(s2);
	min_len = len1;
	if (len2 < min_len)
		min_len = len2;
	cmp = ft_strncmp(s1, s2, min_len);
	if (cmp)
		return (cmp);
	return (len1 - len2);
}

t_env	*find_min_node(t_env *current)
{
	t_env	*min;
	t_env	*comp;

	min = current;
	comp = current->next;
	while (comp)
	{
		if (compare_env_vars(min->value, comp->value) > 0)
			min = comp;
		comp = comp->next;
	}
	return (min);
}

int	sort_env(t_env *exp)
{
	t_env	*current;
	char	*swap;
	t_env	*min;

	current = exp;
	while (current)
	{
		min = find_min_node(current);
		if (min != current)
		{
			swap = current->value;
			current->value = min->value;
			min->value = swap;
		}
		current = current->next;
	}
	return (1);
}
