/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_str_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:04:28 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/06 15:25:03 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pf_str_fd(char *s, int fd)
{
	size_t	total_len;

	if (!s)
		return (write(1, "(null)", 6));
	total_len = ft_strlen(s);
	while (*s)
	{
		if (ft_pf_char_fd(*s++, fd) == -1)
			return (-1);
	}
	return (total_len);
}
