/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 03:21:21 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/06 15:33:14 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*ft_free_content(t_list *cur_node)
{
	t_fd_stat	*cur_fd_stat;

	cur_fd_stat = (t_fd_stat *)(cur_node->content);
	free (cur_fd_stat->str);
	free (cur_fd_stat);
	return (NULL);
}

char	*ft_del_fd_stat(t_list **list, t_list *target)
{
	ft_lstdel_node(list, target, ft_free_content(target));
	return (NULL);
}

t_list	*ft_create_fd_stat(t_list **list, int fd)
{
	t_list		*new_node;
	t_fd_stat	*new_fd_stat;

	new_fd_stat = (t_fd_stat *)malloc(sizeof(t_fd_stat));
	if (!new_fd_stat)
		return (NULL);
	new_fd_stat->fd = fd;
	new_fd_stat->str = ft_strdup("");
	if (!new_fd_stat->str)
		return (NULL);
	new_node = ft_lstnew(new_fd_stat);
	if (!new_node)
		return (NULL);
	ft_lstadd_back(list, new_node);
	return (new_node);
}

t_list	*ft_find_fd_stat(t_list **list, int fd)
{
	t_list	*cur_node;

	cur_node = *list;
	while (cur_node)
	{
		if (((t_fd_stat *)(cur_node->content))->fd == fd)
			return (cur_node);
		cur_node = cur_node->next;
	}
	return (ft_create_fd_stat(list, fd));
}
