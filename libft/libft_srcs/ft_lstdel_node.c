/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:40:15 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/06 13:40:17 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel_node(t_list **list, t_list *target, void (*del)(void *))
{
	t_list	*prev_node;
	t_list	*cur_node;

	prev_node = NULL;
	cur_node = *list;
	while (cur_node != target)
	{
		prev_node = cur_node;
		cur_node = cur_node->next;
	}
	if (prev_node == NULL)
		*list = cur_node->next;
	else
		prev_node->next = cur_node->next;
	ft_lstdelone(cur_node, del);
	return ;
}
