/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:06:35 by yonghyle          #+#    #+#             */
/*   Updated: 2022/12/02 15:18:29 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*_new;
	size_t			over_check;

	over_check = 0;
	if (count != 0 && size != 0)
	{
		over_check = count * size;
		if (over_check / count != size)
			return (0);
	}
	_new = malloc(over_check);
	if (!_new)
		return (0);
	ft_bzero(_new, over_check);
	return (_new);
}
