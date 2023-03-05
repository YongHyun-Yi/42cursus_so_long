/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_hexlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 17:01:14 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/06 14:52:53 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_pf_hexlen(unsigned long long hex)
{
	unsigned long long	decimal;
	int					cnt;

	decimal = 1;
	cnt = 1;
	while (hex / decimal >= 16)
	{
		decimal *= 16;
		cnt++;
	}
	return (cnt);
}
