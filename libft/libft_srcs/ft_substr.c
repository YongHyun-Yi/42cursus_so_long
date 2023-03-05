/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:58:45 by yonghyle          #+#    #+#             */
/*   Updated: 2022/11/21 10:33:57 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	dup_i;
	char	*sub_s;

	if (start >= ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	sub_s = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub_s)
		return (0);
	dup_i = 0;
	while (dup_i < len)
	{
		sub_s[dup_i] = s[dup_i + start];
		dup_i++;
	}
	sub_s[dup_i] = 0;
	return (sub_s);
}
