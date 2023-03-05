/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 09:00:19 by yonghyle          #+#    #+#             */
/*   Updated: 2022/11/20 19:38:16 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(const char *serch_start, const char *needle)
{
	while (*serch_start++ == *needle++)
	{
		if (!*needle)
			return (1);
	}
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*haystack_ptr;

	if (!ft_strlen(needle))
		return ((char *)haystack);
	else if (ft_strlen(haystack) < ft_strlen(needle) || !len
		|| ft_strlen(needle) > len)
		return (0);
	haystack_ptr = haystack;
	while (*haystack_ptr
		&& (size_t)(haystack_ptr - haystack) <= len - ft_strlen(needle))
	{
		if (*haystack_ptr == *needle)
			if (check(haystack_ptr, needle))
				return ((char *)haystack_ptr);
		haystack_ptr++;
	}
	return (0);
}
