/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_data_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 16:29:35 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/08 08:55:42 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_get_print_length(t_flags flg, t_print_data	*pd)
{
	char	sp;

	sp = flg.specifier;
	if (sp == 'd' || sp == 'i' || sp == 'u')
		pd->print_length = ft_pf_nbrlen((pd->nbr), sp != 'u');
	if (sp == 'x' || sp == 'X' || sp == 'p')
		pd->print_length = ft_pf_hexlen(pd->hex);
	if (flg.prc_enable && (!pd->nbr && !pd->hex && !flg.precision))
		pd->print_length = 0;
	if (sp == 'c' || sp == '%')
		pd->print_length = 1;
	if (sp == 's')
	{
		pd->print_length = ft_strlen(pd->str);
		if (flg.prc_enable && pd->print_length > (size_t)flg.precision)
			pd->print_length = flg.precision;
	}
}

static void	ft_get_prefix(t_flags flg, t_print_data	*pd)
{
	char	sp;

	pd->prefix = "";
	sp = flg.specifier;
	if (sp == 'd' || sp == 'i')
	{
		if (flg.space)
			pd->prefix = " ";
		if (flg.plus)
			pd->prefix = "+";
		if (pd->nbr < 0)
			pd->prefix = "-";
	}
	if (sp == 'p' || (sp == 'x' && (flg.sharp && pd->hex)))
		pd->prefix = "0x";
	if (sp == 'X' && (flg.sharp && pd->hex))
		pd->prefix = "0X";
}

static void	ft_get_arg(t_flags flg, t_print_data *pd, va_list ap)
{
	char	sp;

	sp = flg.specifier;
	if (sp == 'c')
		pd->c = va_arg(ap, int);
	if (sp == '%')
		pd->c = '%';
	if (sp == 's')
	{
		pd->str = va_arg(ap, char *);
		if (!pd->str)
			pd->str = "(null)";
	}
	if (sp == 'd' || sp == 'i' || sp == 'u')
		pd->nbr = va_arg(ap, int);
	if (sp == 'p')
		pd->hex = (unsigned long long)va_arg(ap, void *);
	if (sp == 'x' || sp == 'X')
		pd->hex = (unsigned long long)va_arg(ap, unsigned int);
}

t_print_data	ft_get_print_data(const char **str, va_list ap)
{
	t_flags			flg;
	t_print_data	pd;

	flg = ft_get_flags(str);
	ft_bzero(&pd, sizeof(t_print_data));
	ft_get_arg(flg, &pd, ap);
	ft_get_prefix(flg, &pd);
	ft_get_print_length(flg, &pd);
	if (!flg.minus && flg.zero)
		pd.zero = flg.width - ft_strlen(pd.prefix) - pd.print_length;
	if (flg.prc_enable && flg.specifier != 's')
		pd.zero = flg.precision - pd.print_length;
	if (pd.zero < 0)
		pd.zero = 0;
	pd.blank = flg.width - ft_strlen(pd.prefix) - pd.zero - pd.print_length;
	if (pd.blank < 0)
		pd.blank = 0;
	pd.left_justify = flg.minus;
	pd.specifier = flg.specifier;
	return (pd);
}
