/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_nbrlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 17:00:09 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/06 14:53:15 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_pf_nbrlen(int n, int is_signed_int)
{
	unsigned int	us_n;
	int				decimal;
	int				cnt;

	if (n < 0 && is_signed_int)
		us_n = (unsigned int)(n * -1);
	else
		us_n = (unsigned int)n;
	decimal = 1;
	cnt = 1;
	while (us_n / decimal >= 10)
	{
		decimal *= 10;
		cnt++;
	}
	return (cnt);
}
