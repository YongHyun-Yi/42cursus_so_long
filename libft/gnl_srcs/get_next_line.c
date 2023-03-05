/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 03:21:23 by yonghyle          #+#    #+#             */
/*   Updated: 2023/03/02 04:23:23 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_extract_line(t_fd_stat *fd)
{
	char	*src;
	char	*result;
	char	*ext_ptr;
	size_t	ext_pos;

	src = fd->str;
	ext_ptr = src;
	while (*ext_ptr && *ext_ptr != '\n')
		ext_ptr++;
	ext_pos = ext_ptr - src;
	result = ft_substr(src, 0, ext_pos + 1);
	if (!result)
		return (NULL);
	fd->str = ft_substr(src, ext_pos + 1, -1);
	free(src);
	if (!fd->str)
	{
		free(result);
		return (NULL);
	}
	return (result);
}

static int	ft_read_check(t_fd_stat *fd)
{
	int		read_size;
	char	buf[BUFFER_SIZE + 1];
	char	*new_str;

	while (!ft_strchr(fd->str, '\n'))
	{
		read_size = read(fd->fd, buf, BUFFER_SIZE);
		if (read_size < 0 || (read_size == 0 && !*(fd->str)))
			return (0);
		if (read_size == 0 && *(fd->str))
			break ;
		buf[read_size] = '\0';
		new_str = ft_strjoin(fd->str, buf);
		if (!new_str)
			return (0);
		free(fd->str);
		fd->str = new_str;
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_list		*list;
	t_list				*cur_node;
	t_fd_stat			*cur_fd_stat;
	char				*result_line;

	cur_node = ft_find_fd_stat(&list, fd);
	if (!cur_node)
		return (NULL);
	cur_fd_stat = cur_node->content;
	if (ft_read_check(cur_fd_stat))
	{
		result_line = ft_extract_line(cur_fd_stat);
		if (result_line)
			return (result_line);
	}
	ft_del_fd_stat(&list, cur_node);
	return (NULL);
}
