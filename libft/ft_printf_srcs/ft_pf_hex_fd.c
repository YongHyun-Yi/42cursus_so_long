/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_hex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 20:41:39 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/06 14:55:23 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pf_hex_fd(unsigned long long hex, int fd, int is_uppercase)
{
	size_t				total_len;
	unsigned long long	decimal;
	char				*hex_map;

	total_len = ft_pf_hexlen(hex);
	hex_map = "0123456789abcdef";
	if (is_uppercase)
		hex_map = "0123456789ABCDEF";
	decimal = 1;
	while (hex / decimal >= 16)
		decimal *= 16;
	while (decimal)
	{
		if (ft_pf_char_fd(hex_map[hex / decimal], fd) == -1)
			return (-1);
		hex -= (hex / decimal) * decimal;
		decimal /= 16;
	}
	return (total_len);
}
