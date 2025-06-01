/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 01:35:08 by sel-abbo          #+#    #+#             */
/*   Updated: 2024/11/08 17:54:18 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

//#include <stdio.h>
// int main()
//{
// void del(void *content)
// {
// 	free(content);
// }
//	t_list *list;
//	t_list *node1 = ft_lstnew("achraf1");
//	t_list *node2 = ft_lstnew("achraf0");
//	t_list *node3 = ft_lstnew("soufiane");
//
//	list = node1;
//	node1->next = node2;
//	node2->next = node3;
//
//	// printf("%d\n", ft_lstsize(node1));
//	printf("%d\n", ft_lstsize(list));
//
//	return (0);
//}