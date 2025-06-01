/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:09:58 by sel-abbo          #+#    #+#             */
/*   Updated: 2024/11/12 02:01:43 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*str;
	int		s;

	s = ft_strlen(src);
	str = malloc(s + 1);
	if (!str)
		return (0);
	ft_memcpy(str, src, s);
	str[s] = '\0';
	return (str);
}
