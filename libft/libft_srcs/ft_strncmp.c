/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 08:52:29 by yonghyle          #+#    #+#             */
/*   Updated: 2022/11/15 10:24:10 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1_ptr;
	unsigned char	*s2_ptr;

	if (!n)
		return (0);
	s1_ptr = (unsigned char *)s1;
	s2_ptr = (unsigned char *)s2;
	while (--n && *s1_ptr && *s2_ptr)
	{
		if ((*s1_ptr != *s2_ptr) || (n == 0))
			break ;
		s1_ptr++;
		s2_ptr++;
	}
	if (*s1_ptr > *s2_ptr)
		return (1);
	else if (*s1_ptr == *s2_ptr)
		return (0);
	else
		return (-1);
}
