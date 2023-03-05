/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:09:54 by yonghyle          #+#    #+#             */
/*   Updated: 2022/11/15 14:40:39 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*dest_ptr;
	unsigned char	*src_ptr;

	if (!dest && !src)
		return (0);
	dest_ptr = (unsigned char *)dest;
	src_ptr = (unsigned char *)src;
	if (dest_ptr <= src_ptr)
	{
		while (len--)
			*dest_ptr++ = *src_ptr++;
	}
	else
	{
		dest_ptr += len - 1;
		src_ptr += len - 1;
		while (len--)
			*dest_ptr-- = *src_ptr--;
	}
	return (dest);
}
