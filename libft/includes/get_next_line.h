/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 03:21:26 by yonghyle          #+#    #+#             */
/*   Updated: 2023/01/13 11:40:03 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

typedef struct s_fd_stat
{
	int		fd;
	char	*str;
}	t_fd_stat;

char	*get_next_line(int fd);

t_list	*ft_create_fd_stat(t_list **list, int fd);
t_list	*ft_find_fd_stat(t_list **list, int fd);
char	*ft_del_fd_stat(t_list **list, t_list *target);

#endif