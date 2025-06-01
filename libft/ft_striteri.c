/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:19:24 by sel-abbo          #+#    #+#             */
/*   Updated: 2024/11/06 17:41:57 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (*s)
	{
		f(i, s);
		i++;
		s++;
	}
}

// void modify_char(unsigned int index, char *c)
//{
//	if (c[index] >= 'a' && c[index] <= 'z')
//		*(c + index) -=32;
//}
//#include <stdio.h>
// int main(void)
//{
//    char original[] = "eHlol,wrlod!";
//    ft_striteri(original, modify_char);
//	printf("%s\n", original);
//}
