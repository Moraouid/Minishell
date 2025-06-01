/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 21:08:32 by sel-abbo          #+#    #+#             */
/*   Updated: 2024/11/08 18:29:19 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digit(long n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long	b;
	char	*res;
	int		c;

	b = n;
	c = count_digit(b);
	res = malloc(c + 1);
	if (!res)
		return (NULL);
	if (b == 0)
		res[0] = '0';
	res[c] = '\0';
	if (b < 0)
	{
		res[0] = '-';
		b *= -1;
	}
	while (b != 0)
	{
		res[--c] = (b % 10) + 48;
		b = b / 10;
	}
	return (res);
}
/*
 #include <stdio.h>
 int main()
{
	printf("%s\n", ft_itoa(2147483684));
} */
