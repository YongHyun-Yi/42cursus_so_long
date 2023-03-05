/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_intdup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:50:30 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/27 17:15:59 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check_intdup(char *bit_array, unsigned int num)
{
	int	div;
	int	mod;

	if (!bit_array)
		return (0);
	div = num / 8;
	mod = num % 8;
	if (*(bit_array + div) & (1 << mod))
		return (0);
	*(bit_array + div) = (*(bit_array + div) | (1 << mod));
	return (1);
}
