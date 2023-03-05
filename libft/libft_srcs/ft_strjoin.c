/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:28:43 by yonghyle          #+#    #+#             */
/*   Updated: 2022/11/21 10:26:11 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	char	*new_str_ptr;
	size_t	size;

	size = ft_strlen(s1) + ft_strlen(s2);
	new_str = ((char *)malloc(sizeof(char) * (size + 1)));
	if (!new_str)
		return (0);
	new_str_ptr = new_str;
	while (*s1)
		*new_str_ptr++ = *s1++;
	while (*s2)
		*new_str_ptr++ = *s2++;
	*new_str_ptr = '\0';
	return (new_str);
}
