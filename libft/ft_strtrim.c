/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:26:54 by sel-abbo          #+#    #+#             */
/*   Updated: 2024/11/08 18:31:02 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	check_set(char c, char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	i;
	size_t	size;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	size = ft_strlen(s1);
	while (s1[i] && check_set(s1[i], (char *)set))
		i++;
	while (size > i && check_set(s1[size - 1], (char *)set))
		size--;
	res = (char *)malloc(size - i + 1);
	if (!res)
		return (0);
	ft_strlcpy(res, s1 + i, size - i + 1);
	return (res);
}
