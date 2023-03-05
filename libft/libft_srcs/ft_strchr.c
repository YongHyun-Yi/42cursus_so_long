/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:34:13 by yonghyle          #+#    #+#             */
/*   Updated: 2022/11/21 10:11:51 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	check;

	check = (char)c;
	if (check == '\0')
		return ((char *)str + ft_strlen(str));
	while (*str)
	{
		if (*str == check)
			return ((char *)str);
		str++;
	}
	return (0);
}
