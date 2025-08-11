/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 14:07:25 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/08/10 20:54:32 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_expandable(char c)
{
	return (c == '_' || ft_isalpha(c) || c == '?' || c == '"' || c == '\'');
}

int	find_dollar_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && is_expandable(str[i + 1]))
			return (1);
		i++;
	}
	return (0);
}

char	*random_str(t_shell *shell)
{
	char	buffer[200];
	char	*r_str;

	int (i), (j), (fd), (b_read);
	r_str = gc_malloc(&shell->gc, 10);
	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
		return (perror("Niggshell"), NULL);
	b_read = read(fd, buffer, 200);
	if (b_read == -1)
		return (close(fd), NULL);
	i = 0;
	j = 0;
	while (i < 9)
	{
		if (isalpha(buffer[j]))
			r_str[i++] = buffer[j];
		j++;
	}
	r_str[i] = '\0';
	close(fd);
	return (r_str);
}

char	*get_expanded_value(char *value, int *i, t_shell *shell)
{
	int		start;
	char	*var;
	t_env	*env;

	(*i)++;
	start = *i;
	if (value[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(shell->last_exit_status, &shell->gc));
	}
	else if (!ft_isalnum(value[*i]) && value[*i] != '_')
		return (ft_strdup("$", &shell->gc));
	while (value[*i] && (ft_isalnum(value[*i]) || value[*i] == '_'))
		(*i)++;
	var = ft_substr(value, start, *i - start, &shell->gc);
	env = find_env_var(shell->env, var);
	if (env && ft_strchr(env->value, '='))
		return (ft_strdup(ft_strchr(env->value, '=') + 1, &shell->gc));
	else
		return (ft_strdup("", &shell->gc));
}

void	expand_variable(char *value, int *i, t_shell *shell, char **res)
{
	char	*e_value;

	e_value = get_expanded_value(value, i, shell);
	*res = ft_strjoin(*res, shell->r_str, &shell->gc);
	*res = ft_strjoin(*res, e_value, &shell->gc);
	*res = ft_strjoin(*res, shell->r_str, &shell->gc);
}
