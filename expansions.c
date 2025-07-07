/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:16:59 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/07/04 19:35:14 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_env_var(t_env *env, char *name)
{
	while (env)
	{
		if (!ft_strncmp(env->value, name, ft_strlen(name))
			&& env->value[ft_strlen(name)] == '=')
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	find_dollar_sign(char *str)
{
	while (*str)
	{
		if (*str == '$')
			return (1);
		str++;
	}
	return (0);
}

void	handle_expand(char *value, t_shell *shell)
{
	t_env	*env;
	char	*word;
	char	*name;
	char	*eq;
	int		i;
	int		j;

	word = ft_strdup("");
	i = 0;
	while (value[i] && value[i] != '$')
		i++;
	if (i > 0)
		word = ft_substr(value, 0, i);
	if (value[i] == '$')
	{
		i++;
		j = i;
		while (value[i] && ft_isalnum(value[i]))
			i++;
		name = ft_substr(value, j, i - j);
		printf("<--------%s\n", name);
		env = find_env_var(shell->env, name);
		if (env)
		{
			eq = ft_strchr(env->value, '=');
			word = ft_strjoin(word, eq + 1);
		}
	}
	printf("---->%s\n", word);
}

// void	expansions(t_shell *shell)
// {
// 	t_token	*current;
//
// 	// t_env		*env_var;
// 	// int 		i = 0;
// 	current = shell->tokens;
// 	while (current)
// 	{
// 		if (current->type == WORD)
// 		{
// 			if (find_dollar_sign(current->value))
// 			{
// 				handle_expand(current->value, shell);
// 			}
// 		}
// 		current = current->next;
// 	}
// 	shell->cmd = split_commands(shell->tokens);
// }
