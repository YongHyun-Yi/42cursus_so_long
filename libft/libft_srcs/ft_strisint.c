/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:26:16 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/27 17:16:30 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strisint(char *str)
{
	char	*str_ptr;

	if (!str)
		return (0);
	str_ptr = str;
	if (*str_ptr == '-' || *str_ptr == '+')
		str_ptr++;
	if (!*str_ptr || !ft_strisnum(str_ptr))
		return (0);
	while (*str_ptr == '0')
		str_ptr++;
	if (!*str_ptr)
		return (1);
	else if (ft_strlen(str_ptr) > 10)
		return (0);
	else if (ft_strlen(str_ptr) == 10)
	{
		if (*str_ptr > '2')
			return (0);
	}
	if ((ft_atoi(str) < 0) != (*str == '-'))
		return (0);
	return (1);
}
