/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 20:22:25 by sel-abbo          #+#    #+#             */
/*   Updated: 2024/11/11 22:36:22 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

// #include <stdio.h>
//  int main()
//  {

//  	t_list *node1 = ft_lstnew("achraf1");
//  	t_list *node2 = ft_lstnew("achraf0");
//  	t_list *node3 = ft_lstnew("soufiane");

//  	node1->next = node2;
//  	node2->next = node3;

//  	printf("%d\n", ft_lstsize(node1));

//  	return (0);
// }