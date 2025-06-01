/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:53:54 by sel-abbo          #+#    #+#             */
/*   Updated: 2024/11/06 17:39:36 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*t_new;

	t_new = malloc(sizeof(t_list));
	if (!t_new)
		return (NULL);
	t_new->content = content;
	t_new->next = NULL;
	return (t_new);
}
// #include <stdio.h>
// int main()
// {
//     char *s = "achraf";
//     t_list  *node = ft_lstnew(s);
//     printf("%s\n" , (char *)node -> content);
// }