/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:16:59 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/07/26 20:14:13 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_expandable(char c)
{
	return (c == '_' || ft_isalpha(c) || c == '?');
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

	int(i), (j), (fd), (b_read);
	fd = open("/dev/random", O_RDONLY);
	b_read = read(fd, buffer, 200);
	r_str = gc_malloc(&shell->gc, 10);
	i = 0;
	j = 0;
	while (i < 9)
	{
		if (isalpha(buffer[j]))
		{
			r_str[i] = buffer[j];
			i++;
		}
		j++;
		if (j > 200)
		{
			j = 0;
			b_read = read(fd, buffer, 200);
		}
	}
	r_str[i] = '\0';
	close(fd);
	return (r_str);
}

int	s_quote(char *value, t_shell *shell, char **res)
{
	int		i;
	char	*sub;

	i = 1;
	while (value[i] != '\'')
		i++;
	sub = ft_substr(value, 0, i + 1, &shell->gc); //
	*res = ft_strjoin(*res, sub, &shell->gc);
	return (i + 1);
}

void	expand_variable(char *value, int *i, t_shell *shell, char **res)
{
	int		start;
	char	*var;
	char	*e_value;
	t_env	*env;

	(*i)++;
	start = *i;
	if (value[*i] == '?')
	{
		e_value = ft_itoa(shell->last_exit_status, &shell->gc);
		(*i)++;
	}
	else
	{
		while (value[*i] && (ft_isalnum(value[*i]) || value[*i] == '_'))
			(*i)++;
		var = ft_substr(value, start, *i - start, &shell->gc);
		env = find_env_var(shell->env, var);
		if (env && ft_strchr(env->value, '='))
			e_value = ft_strdup(ft_strchr(env->value, '=') + 1, &shell->gc);
		else
			e_value = ft_strdup("", &shell->gc);
	}
	*res = ft_strjoin(*res, shell->r_str, &shell->gc);
	*res = ft_strjoin(*res, e_value, &shell->gc);
	*res = ft_strjoin(*res, shell->r_str, &shell->gc);
}

int	d_quote(char *value, t_shell *shell, char **res)
{
	int		i;
	int		start;
	char	*sub;

	i = 0;
	while (value[i])
	{
		if (value[i] == '$')
			expand_variable(value, &i, shell, res);
		else
		{
			start = i;
			while (value[i] && value[i] != '$')
				i++;
			sub = ft_substr(value, start, i - start, &shell->gc);
			*res = ft_strjoin(*res, sub, &shell->gc);
		}
	}
	return (i + 1);
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
		if (value[i] == '\'' || value[i] == '"')
		{
			if (value[i] == '"')
				i += d_quote(&value[i], shell, &result);
			if (value[i] == '\'')
				i += s_quote(&value[i], shell, &result);
		}
		else
			i += n_quote(&value[i], shell, &result);
	}
	return (result);
}

int	count_for_split(char *value, char *r_str)
{
	int(i), (dq), (sq), (rq), (count);
	(1) && (i = 0, dq = 0, sq = 0, rq = 0);
	count = 0;
	while (value[i])
	{
		if (value[i] == '"' && !sq && !rq)
			dq = !dq;
		if (value[i] == '\'' && !dq && !rq)
			sq = !sq;
		if (!ft_strncmp(&value[i], r_str, 9) && !dq && !sq)
			rq = !rq;
		if (isspace(value[i]) && rq)
		{
			while (isspace(value[i]))
				i++;
			count++;
		}
		else
			i++;
	}
	count++;
	return (count);
}

char	**e_split(char *value, char *r_str, int count, t_shell *shell)
{
	char	**res;

	int(i), (j), (sq), (dq), (rq), (start);
	(1) && (sq = 0, dq = 0, rq = 0);
	res = gc_malloc(&shell->gc, (count + 1) * sizeof(char *));
	i = 0;
	start = 0;
	j = 0;
	while (value[i])
	{
		if (value[i] == '"' && !sq && !rq)
			dq = !dq;
		if (value[i] == '\'' && !dq && !rq)
			sq = !sq;
		if (!ft_strncmp(&value[i], r_str, 9) && !dq && !sq)
			rq = !rq;
		if ((isspace(value[i]) && rq))
		{
			res[j] = ft_substr(value, start, i - start, &shell->gc);
			while (isspace(value[i]))
				i++;
			start = i;
			j++;
		}
		else
			i++;
	}
	if (i > start)
		res[j] = ft_strdup(&value[start], &shell->gc);
	res[j + 1] = NULL;
	return (res);
}

void	split_after_expand(t_shell *shell, t_token *tokens, char *j_str)
{
	int		count;
	char	**split;
	int		i;
	t_token	*current;
	t_token	*s_next;
	t_token	*n_token;

	i = 1;
	current = tokens;
	s_next = tokens->next;
	count = count_for_split(j_str, shell->r_str);
	split = e_split(j_str, shell->r_str, count, shell);
	current->value = split[0];
	while (split[i])
	{
		n_token = NULL;
		current->type = AMBGUS;
		n_token = creat_node_cmd(shell, split[i], AMBGUS);
		current->next = n_token;
		current = current->next;
		i++;
	}
	current->next = s_next;
}

int	len_allocate(char *str, char *r_str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (!ft_strncmp(&str[i], r_str, 9))
			i += 9;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

void	remove_expand_quotes(t_token *tokens, char *r_str, t_gc_node **gc)
{
	t_token	*current;
	char	*value;
	int		len;
	int		j;
	int		i;

	current = tokens;
	while (current)
	{
		i = 0;
		len = len_allocate(current->value, r_str);
		value = gc_malloc(gc, len + 1);
		j = 0;
		while (current->value[i])
		{
			if (!ft_strncmp(&current->value[i], r_str, 9))
				i += 9;
			else
				value[j++] = current->value[i++];
		}
		value[j] = '\0';
		current->value = value;
		current = current->next;
	}
}

void	expansions(t_shell *shell)
{
	t_token	*current;
	char	*j_str;

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
				split_after_expand(shell, current, j_str);
			}
		}
		current = current->next;
	}
	remove_expand_quotes(shell->tokens, shell->r_str, &shell->gc);
}
