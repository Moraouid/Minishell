/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:16:59 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/08/11 22:47:59 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	s_quote(char *value, t_shell *shell, char **res)
{
	int		i;
	char	*sub;

	i = 1;
	while (value[i] != '\'')
		i++;
	sub = ft_substr(value, 0, i + 1, &shell->gc);
	*res = ft_strjoin(*res, sub, &shell->gc);
	return (i + 1);
}

int	d_quote(char *value, t_shell *shell, char **res)
{
	int		i;
	int		start;
	char	*sub;

	i = 1;
	*res = ft_strjoin(*res, "\"", &shell->gc);
	while (value[i] && value[i] != '"')
	{
		if (value[i] == '$')
			expand_variable(value, &i, shell, res);
		else
		{
			start = i;
			while (value[i] && value[i] != '$' && value[i] != '"')
				i++;
			sub = ft_substr(value, start, i - start, &shell->gc);
			*res = ft_strjoin(*res, sub, &shell->gc);
		}
	}
	*res = ft_strjoin(*res, "\"", &shell->gc);
	i++;
	return (i);
}

int	n_quote(char *value, t_shell *shell, char **res)
{
	int		i;
	int		start;
	char	*sub;

	i = 0;
	while (value[i] && value[i] != '\'' && value[i] != '"')
	{
		if (value[i] == '$')
			expand_variable(value, &i, shell, res);
		else
		{
			start = i;
			while (value[i] && value[i] != '$' && value[i] != '\''
				&& value[i] != '"')
				i++;
			sub = ft_substr(value, start, i - start, &shell->gc);
			*res = ft_strjoin(*res, sub, &shell->gc);
		}
	}
	return (i);
}

char	*handle_expand(char *value, t_shell *shell)
{
	char	*result;
	int		i;

	i = 0;
	result = ft_strdup("", &shell->gc);
	while (value[i])
	{
		if (value[i] == '"')
			i += d_quote(&value[i], shell, &result);
		if (value[i] == '\'')
			i += s_quote(&value[i], shell, &result);
		else
			i += n_quote(&value[i], shell, &result);
	}
	return (result);
}

void	expansions(t_shell *shell)
{
	char	*j_str;
	t_token	*current;

	shell->r_str = random_str(shell);
	j_str = ft_strdup("", &shell->gc);
	current = shell->tokens;
	while (current)
	{
		if (current->type == WORD)
		{
			if (find_dollar_sign(current->value))
			{
				j_str = handle_expand(current->value, shell);
				current->value = j_str;
				split_after_expand(shell, &current, j_str);
			}
		}
		current = current->next;
	}
}
