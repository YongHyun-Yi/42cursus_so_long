/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 10:09:37 by yonghyle          #+#    #+#             */
/*   Updated: 2022/11/17 17:56:39 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	index;
	char			*new_s;

	new_s = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!new_s)
		return (0);
	index = 0;
	while (s[index])
	{
		new_s[index] = f(index, s[index]);
		index++;
	}
	new_s[index] = '\0';
	return (new_s);
}
