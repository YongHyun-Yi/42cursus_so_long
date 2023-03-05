/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:14:52 by yonghyle          #+#    #+#             */
/*   Updated: 2022/11/21 10:30:46 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t d_size)
{
	size_t		dest_len;
	size_t		src_len;
	const char	*src_ptr;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (d_size <= dest_len)
		return (d_size + src_len);
	dest += dest_len;
	src_ptr = src;
	while (*src_ptr && (unsigned long)(src_ptr - src + 1) < d_size - dest_len)
		*dest++ = *src_ptr++;
	*dest = '\0';
	return (dest_len + src_len);
}
