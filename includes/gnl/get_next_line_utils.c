/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:20:21 by sel-abbo          #+#    #+#             */
/*   Updated: 2024/12/12 19:20:04 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_r(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*res;
	size_t	len_s1;
	size_t	len_s2;

	i = 0;
	j = 0;
	len_s1 = ft_strlen1(s1);
	len_s2 = ft_strlen1(s2);
	res = (char *)malloc(len_s1 + len_s2 + 1);
	if (!res)
		return (0);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	free(s1);
	return (res);
}

char	*ft_strchr1(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (!c)
		return ((char *)&s[i]);
	return (NULL);
}

size_t	ft_strlen1(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr1(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	len_a;

	i = 0;
	if (!s || start > ft_strlen1(s))
		return (NULL);
	len_a = ft_strlen1(s) - start;
	if (len > len_a)
		len = len_a;
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	while (s[start] && i < len)
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}

char	*ft_strdup1(const char *src)
{
	char	*str;
	int		s;
	int		i;

	s = ft_strlen1(src);
	str = malloc(s + 1);
	if (!src)
		return (NULL);
	i = 0;
	while (i < s)
	{
		str[i] = src[i];
		i++;
	}
	str[s] = '\0';
	return (str);
}
