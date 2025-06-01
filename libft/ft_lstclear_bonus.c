/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 02:01:20 by sel-abbo          #+#    #+#             */
/*   Updated: 2024/11/09 22:36:15 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*str;
	t_list	*tmp;

	if (!lst || !del)
		return ;
	str = *lst;
	while (str)
	{
		tmp = str->next;
		ft_lstdelone(str, del);
		str = tmp;
	}
	*lst = NULL;
}
