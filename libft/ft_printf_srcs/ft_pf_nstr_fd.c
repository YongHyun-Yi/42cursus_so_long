/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_nstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 17:03:36 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/06 14:55:57 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pf_nstr_fd(char *s, int fd, size_t n)
{
	int	total_len;

	if (n > ft_strlen(s))
		n = ft_strlen(s);
	total_len = n;
	while (n--)
	{
		if (ft_pf_char_fd(*s++, fd) == -1)
			return (-1);
	}
	return (total_len);
}
