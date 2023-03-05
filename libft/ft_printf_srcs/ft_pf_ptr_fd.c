/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_ptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 20:39:42 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/06 14:56:16 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pf_ptr_fd(void *ptr, int fd)
{
	if (ft_pf_str_fd("0x", fd) == -1)
		return (-1);
	if (ft_pf_hex_fd((unsigned long long)ptr, fd, 0) == -1)
		return (-1);
	return (ft_pf_hexlen((unsigned long long)ptr) + 2);
}
