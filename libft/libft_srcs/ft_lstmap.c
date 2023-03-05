/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:00:31 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/15 10:40:14 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start_of_lst;
	t_list	*new_lst;
	t_list	*current;
	void	*new_content;

	start_of_lst = 0;
	if (lst || f || del)
	{
		current = lst;
		while (current)
		{
			new_content = f(current->content);
			new_lst = ft_lstnew(new_content);
			if (!new_lst)
			{
				del(new_content);
				ft_lstclear(&start_of_lst, del);
				return (0);
			}
			ft_lstadd_back(&start_of_lst, new_lst);
			current = current->next;
		}
		return (start_of_lst);
	}
	return (0);
}
