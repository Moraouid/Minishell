/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 10:55:08 by zatais            #+#    #+#             */
/*   Updated: 2025/08/03 16:11:39 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2, t_gc_node **gc)
{
	size_t	len1;
	size_t	len2;
	char	*res;
	size_t	i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = gc_malloc(gc, len1 + len2 + 1);
	i = 0;
	while (*s1)
		res[i++] = *s1++;
	while (*s2)
		res[i++] = *s2++;
	res[i] = '\0';
	return (res);
}

char	*ft_strndup(char *s, size_t n, t_gc_node **gc)
{
	char	*res;
	size_t	i;

	i = 0;
	res = gc_malloc(gc, n + 1);
	while (i < n)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strdup(char *s, t_gc_node **gc)
{
	size_t	len;
	char	*dup;
	size_t	i;

	if (!s)
		return (NULL);
	len = ft_strlen(s) + 1;
	dup = gc_malloc(gc, len);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_substr(char *s, unsigned int start, size_t len, t_gc_node **gc)
{
	char	*sub;
	size_t	i;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup("", gc));
	if (len > s_len - start)
		len = s_len - start;
	sub = gc_malloc(gc, len + 1);
	if (!sub || !s)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
