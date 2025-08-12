/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 22:30:44 by zatais            #+#    #+#             */
/*   Updated: 2025/08/12 21:33:00 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_var_name(char **arg, char **name, t_gc_node **gc)
{
	char	*eq;
	char	*value;

	value = NULL;
	eq = ft_strchr(*arg, '=');
	if (eq)
	{
		*name = ft_strndup(*arg, eq - *arg, gc);
		value = eq + 1;
		if (!ft_strncmp(*name, "SHLVL", 5) && is_full_alpha(value))
			*arg = ft_strjoin(ft_strjoin(*name, "=", gc), ft_itoa(0, gc), gc);
	}
	else
		*name = *arg;
}

int	process_argument(t_env **env, char *arg, t_gc_node **gc)
{
	char	*name;
	t_env	*node;

	get_var_name(&arg, &name, gc);
	if (!valid_identifier(name))
		return (cmd_error2(arg), 0);
	node = find_env_var(*env, name);
	if (node && ft_strchr(arg, '='))
    node->value = ft_strdup(arg, gc);
	else if (!node)
		create_new_node(env, arg, gc);
	return (1);
}

int	handle_export_args(t_env **env, char **args, t_gc_node **gc)
{
	int	ret;
	int	i;

	ret = 0;
	i = -1;
	while (args[++i])
		if (!process_argument(env, args[i], gc))
			++ret;
	if (ret)
		return (1);
	return (0);
}

int	my_export(t_env **env, char **args, t_gc_node **gc)
{
	t_env		*copy_env;
	t_gc_node	*temp_gc;

	if (!args[0])
	{
		temp_gc = NULL;
		copy_env = NULL;
		copy_sort(*env, &copy_env, &temp_gc);
		print_sorted_env(copy_env);
		gc_clean(&temp_gc);
		return (0);
	}
	return (handle_export_args(env, args, gc));
}
