/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:18:34 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/15 11:20:31 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format_handler(t_print_data	pd)
{
	if (pd.specifier == 'c' || pd.specifier == '%')
		return (ft_pf_char_fd(pd.c, 1));
	else if (pd.specifier == 's')
		return (ft_pf_nstr_fd(pd.str, 1, pd.print_length));
	else if (pd.specifier == 'd' || pd.specifier == 'i' || pd.specifier == 'u')
		return (ft_pf_nbr_nosign_fd(pd.nbr, 1, (pd.specifier != 'u')));
	else if (pd.specifier == 'x' || pd.specifier == 'X' || pd.specifier == 'p')
		return (ft_pf_hex_fd(pd.hex, 1, (pd.specifier == 'X')));
	return (-1);
}

int	ft_print_handler(t_print_data	pd)
{
	if (!pd.left_justify && ft_pf_nchar_fd(' ', 1, pd.blank) == -1)
		return (-1);
	if (pd.prefix && ft_pf_nstr_fd(pd.prefix, 1, ft_strlen(pd.prefix)) == -1)
		return (-1);
	if (ft_pf_nchar_fd('0', 1, pd.zero) == -1)
		return (-1);
	if (pd.print_length && ft_format_handler(pd) == -1)
		return (-1);
	if (pd.left_justify && ft_pf_nchar_fd(' ', 1, pd.blank) == -1)
		return (-1);
	return (pd.blank + ft_strlen(pd.prefix) + pd.zero + pd.print_length);
}

int	ft_printf_parsing(const char *str, va_list ap)
{
	int				total_len;
	int				current_len;
	t_print_data	pd;

	if (!str)
		return (-1);
	total_len = 0;
	while (*str)
	{
		if (*str == '%')
		{
			++str;
			pd = ft_get_print_data(&str, ap);
			current_len = ft_print_handler(pd);
		}
		else
			current_len = ft_pf_char_fd(*str, 1);
		if (current_len == -1)
			return (-1);
		total_len += current_len;
		str++;
	}
	return (total_len);
}

int	ft_printf(const char *last, ...)
{
	int		total_len;
	va_list	ap;

	total_len = 0;
	va_start(ap, last);
	total_len = ft_printf_parsing(last, ap);
	va_end(ap);
	return (total_len);
}
