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

#include "libft/libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

char *random_str()
{
  char  buffer[200];
  char  *r_str;
  int   i;
  int   j;
  int fd;
  int b_read;

  fd = open("/dev/random", O_RDONLY);
  b_read = read(fd, buffer, 200);
  r_str = malloc(10);
  i = 0;
  j = 0;
  while(i < 9)
  {
    if(isalpha(buffer[j]))
    {
      r_str[i] = buffer[j];
      i++;
    }
    j++;
    if(j > 200)
    {
      j = 0;
      b_read = read(fd, buffer, 200);
    }
  }
  r_str[i] = '\0';
  return r_str;
}

int s_quote(char *value, t_shell *shell, char **res)
{
  int i;
  char *sub;

  i = 1;
  while(value[i] != '\'')
    i++;
  sub = ft_substr(value, 0, i + 1);
  *res = ft_strjoin(*res, sub);
  free(sub);
  return i + 1;
}

int d_quote(char *value, t_shell *shell, char **res, char *r_str)
{
  int i;
  int start;
  char *var;
  char *e_value;
  t_env *env;
  char *sub;

  i = 1;
  while(value[i] && value[i] != '"')
  {
    if(value[i] == '$')
    {
      i++;
      start = i;
      while(value[i] && (ft_isalnum(value[i]) || value[i] == '_'))
        i++;
      var = ft_substr(value, start, i - start);
      env = find_env_var(shell->env, var);
      if(env && ft_strchr(env->value, '='))
        e_value = ft_strdup(ft_strchr(env->value, '=') + 1);
      else
        e_value = ft_strdup("");
      *res = ft_strjoin(*res, "<<");
      *res = ft_strjoin(*res, e_value);
      *res = ft_strjoin(*res, ">>");
    }
    else
		{
      start = i;
			while (value[i] && value[i] != '$' && value[i] != '"')
				i++;
			sub = ft_substr(value, start, i - start);
			*res = ft_strjoin(*res, sub);
      free(sub);
    }
  }
  return i + 1;
}

int n_quote(char *value, t_shell *shell, char **res, char *r_str)
{
  int i;
  int start;
  char *var;
  char  *sub;
  char *e_value;
  t_env *env;

  i = 0;
  while(value[i] && value[i] != '\'' && value[i] != '"')
  {
    if(value[i] == '$')
    {
      i++;
      start = i;
      while(value[i] && (ft_isalnum(value[i]) || value[i] == '_'))
        i++;
      var = ft_substr(value, start, i - start);
      env = find_env_var(shell->env, var);
      if(env && ft_strchr(env->value, '='))
        e_value = ft_strdup(ft_strchr(env->value, '=') + 1);
      else
        e_value = ft_strdup("");
      *res = ft_strjoin(*res, "<<");
      *res = ft_strjoin(*res, e_value);
      *res = ft_strjoin(*res,">>");
    }
    else
		{
      start = i;
      while (value[i] && value[i] != '$' && value[i] != '\'' && value[i] != '"')
				i++;
			sub = ft_substr(value, start, i - start);
			*res = ft_strjoin(*res, sub);
      free(sub);
    }
  }
  return i;
}

char *handle_expand(char *value, t_shell *shell)
{
  char  *r_str;
	char	*result;
	int		i;

  i = 0;
  result = ft_strdup("");
  r_str = random_str();
	while (value[i])
	{
    if(value[i] == '\'' || value[i] =='"')
    {
      if(value[i] == '"')
        i += d_quote(&value[i], shell, &result, r_str);
      if(value[i] == '\'')
        i += s_quote(&value[i], shell, &result);
    }
    else
      i += n_quote(&value[i], shell, &result, r_str);
    
	}
  printf("%s\n", result);
	return result;
}


void	expansions(t_shell *shell)
{
	t_token	*current;
  char  *j_str;

  j_str = ft_strdup("");
	current = shell->tokens;
	while (current)
	{
		if (current->type == WORD)
		{
			if (find_dollar_sign(current->value))
			{
				j_str = handle_expand(current->value, shell);
			}
		}
		current = current->next;
	}
	// shell->cmd = split_commands(shell->tokens);

}
