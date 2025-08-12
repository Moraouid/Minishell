/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 06:17:02 by zatais            #+#    #+#             */
/*   Updated: 2025/08/12 12:40:33 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_sorted_env(t_env *exp)
{
	char	*eq;

	while (exp)
	{
		if (exp->value[0] == '_' && (exp->value[1] == '\0'
				|| exp->value[1] == '='))
		{
			exp = exp->next;
			continue ;
		}
		eq = ft_strchr(exp->value, '=');
		if (eq)
		{
			*eq = '\0';
			printf("declare -x %s=\"%s\"\n", exp->value, eq + 1);
			*eq = '=';
		}
		else
			printf("declare -x %s\n", exp->value);
		exp = exp->next;
	}
}

void	copy_sort(t_env *env, t_env **exp, t_gc_node **gc)
{
	t_env	*new_node;

	while (env)
	{
		new_node = create_node(env->value, gc);
		add_back(exp, new_node);
		env = env->next;
	}
	sort_env(*exp);
}

int	valid_identifier(char *name)
{
	if (!ft_isalpha(*name) && *name != '_')
		return (0);
	while (*++name)
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (0);
	}
	return (1);
}

int	is_full_alpha(char *val)
{
	int	i;
	int	alpha_count;

	i = -1;
	alpha_count = 0;
	if (ft_isalpha(val[0]) || val[0] == '-')
		return (1);
	while (val[++i])
	{
		if (!(val[i] >= '0' && val[i] <= '9'))
			++alpha_count;
	}
	if (alpha_count)
		return (1);
	return (0);
}

t_env	*find_env_var(t_env *env, char *name)
{
	while (env)
	{
		if (!ft_strncmp(env->value, name, ft_strlen(name))
			&& (env->value[ft_strlen(name)] == '='
				|| env->value[ft_strlen(name)] == '\0'))
			return (env);
		env = env->next;
	}
	return (NULL);
}
