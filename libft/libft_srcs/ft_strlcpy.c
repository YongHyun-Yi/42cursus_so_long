/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:33:13 by yonghyle          #+#    #+#             */
/*   Updated: 2022/11/15 08:12:15 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t d_size)
{
	const char	*src_ptr;

	src_ptr = src;
	while (*src_ptr && (unsigned long)(src_ptr - src) + 1 < d_size)
		*dest++ = *src_ptr++;
	if (d_size)
		*dest = '\0';
	return (ft_strlen(src));
}
