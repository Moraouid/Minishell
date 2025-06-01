/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 00:00:08 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/05/23 02:00:21 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

int	count_word(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (str[i] == 0)
		return (0);
	while (str[i] == c && str[i])
		i++;
	while (str[i])
	{
		if (str[i] == c && str[i - 1] != c)
			count++;
		i++;
	}
	if (str[i - 1] != c)
		count++;
	return (count);
}

static void	ft_free_all(char **res, int h)
{
	while (h >= 0)
		free(res[h--]);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;
	int		j;

	i = 0;
	res = malloc((count_word((char *)s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			j = 0;
			res[i] = malloc((ft_len(s, c) + 1) * sizeof(char));
			if (!res[i])
				return (ft_free_all(res, i), NULL);
			while (*s && *s != c)
				res[i][j++] = *s++;
			res[i++][j] = '\0';
		}
	}
	return (res[i] = NULL, res);
}

// #include <stdio.h>
// int	main()
// {
// 	char **result;
// 	int i;

// 	result = ft_split(",,,,Hello,,world,,this,is,a,test,,,,,,,,ffff,,", ',');
// 	i = 0;
//     while (result[i])
//     {
//     	printf("%s \n", result[i]);
//     	i++;
//     }
// 	    	printf("%s \n", result[i]);
// }
