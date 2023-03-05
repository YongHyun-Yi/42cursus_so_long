/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_nbr_nosign_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 17:04:59 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/06 14:55:38 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pf_nbr_nosign_fd(int n, int fd, int is_signed_int)
{
	unsigned int	us_n;
	int				decimal;

	us_n = (unsigned int)n;
	if (is_signed_int && n < 0)
		us_n = (unsigned int)(n * -1);
	decimal = 1;
	while (us_n / decimal >= 10)
		decimal *= 10;
	while (decimal)
	{
		if (ft_pf_char_fd((us_n / decimal) + '0', fd) == -1)
			return (-1);
		us_n -= (us_n / decimal) * decimal;
		decimal /= 10;
	}
	return (ft_pf_nbrlen(n, is_signed_int));
}
