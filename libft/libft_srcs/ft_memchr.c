/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:16:27 by yonghyle          #+#    #+#             */
/*   Updated: 2022/11/15 10:43:02 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_ptr;
	unsigned char	check;

	s_ptr = (unsigned char *)s;
	check = (unsigned char)c;
	while (n--)
	{
		if (*s_ptr == check)
			return (s_ptr);
		s_ptr++;
	}
	return (0);
}
