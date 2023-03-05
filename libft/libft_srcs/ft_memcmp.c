/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:19:23 by yonghyle          #+#    #+#             */
/*   Updated: 2022/11/15 10:59:41 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_ptr;
	unsigned char	*s2_ptr;

	if (!n)
		return (0);
	s1_ptr = (unsigned char *)s1;
	s2_ptr = (unsigned char *)s2;
	while (--n && *s1_ptr == *s2_ptr)
	{
		s1_ptr++;
		s2_ptr++;
	}
	return (*s1_ptr - *s2_ptr);
}
