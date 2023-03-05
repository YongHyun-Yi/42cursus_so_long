/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:09:24 by yonghyle          #+#    #+#             */
/*   Updated: 2022/11/15 11:16:49 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	char	*s2_ptr;

	s2 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!s2)
		return (0);
	s2_ptr = s2;
	while (*s1)
		*s2_ptr++ = *s1++;
	*s2_ptr = '\0';
	return (s2);
}
