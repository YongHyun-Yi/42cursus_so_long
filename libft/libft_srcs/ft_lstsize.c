/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:56:30 by yonghyle          #+#    #+#             */
/*   Updated: 2022/11/19 20:04:32 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		cnt;
	t_list	*current;

	cnt = 0;
	current = lst;
	while (current)
	{
		current = current->next;
		cnt++;
	}
	return (cnt);
}
