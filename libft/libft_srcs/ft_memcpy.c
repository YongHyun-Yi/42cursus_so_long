/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 09:56:45 by yonghyle          #+#    #+#             */
/*   Updated: 2022/11/15 14:40:46 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_ptr;
	unsigned char	*src_ptr;

	if (!dest && !src)
		return (0);
	dest_ptr = (unsigned char *)dest;
	src_ptr = (unsigned char *)src;
	while (n--)
		*dest_ptr++ = *src_ptr++;
	return (dest);
}
