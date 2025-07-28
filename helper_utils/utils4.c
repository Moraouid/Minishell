/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:18:07 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/07/28 17:18:07 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	*ft_itoa(int n, t_gc_node **gc)
{
	long	b;
	char	*res;
	int		c;

	b = n;
	c = count_digit(b);
	res = gc_malloc(gc, c + 1);
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
