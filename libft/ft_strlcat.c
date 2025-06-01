/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 23:00:05 by sel-abbo          #+#    #+#             */
/*   Updated: 2024/11/08 17:57:16 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	ld;
	size_t	ls;
	size_t	i;

	ld = ft_strlen(dest);
	ls = ft_strlen(src);
	i = 0;
	if (size == 0)
		return (ls);
	if (ld >= size)
		return (size + ls);
	while (src[i] && i + ld < size - 1)
	{
		dest[i + ld] = src[i];
		i++;
	}
	dest[i + ld] = '\0';
	return (ld + ls);
}
//#include <stdio.h>
//
// int main()
//{
//	char *str = "zatais";
//	printf("%ld\n", ft_strlcat(NULL, str, 6));
//}
