/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_nchar_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 17:05:43 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/06 14:55:47 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pf_nchar_fd(char c, int fd, size_t n)
{
	int	total_len;

	total_len = n;
	while (n--)
	{
		if (ft_pf_char_fd(c, fd) == -1)
			return (-1);
	}
	return (total_len);
}
