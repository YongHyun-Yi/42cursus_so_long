/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:58:55 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/15 10:42:23 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next_node;

	if (*lst)
	{
		current = *lst;
		while (current)
		{
			next_node = current->next;
			ft_lstdelone(current, del);
			current = next_node;
		}
		*lst = 0;
	}
}
