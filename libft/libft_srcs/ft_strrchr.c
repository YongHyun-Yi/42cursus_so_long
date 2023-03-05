/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:38:38 by yonghyle          #+#    #+#             */
/*   Updated: 2022/11/21 10:15:31 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t		index;
	char		check;

	check = (char)c;
	index = ft_strlen(str);
	if (check == '\0')
		return ((char *)str + index);
	while (index)
	{
		if (str[--index] == check)
			return ((char *)str + index);
	}
	return (0);
}
