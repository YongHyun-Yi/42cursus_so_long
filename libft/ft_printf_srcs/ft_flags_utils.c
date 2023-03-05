/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:50:59 by yonghyle          #+#    #+#             */
/*   Updated: 2022/12/25 00:40:35 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_get_width_precision(t_flags *flg, const char **str)
{
	if (ft_isdigit(**str))
	{
		flg->width = ft_atoi(*str);
		while (ft_isdigit(**str))
			++*str;
	}
	if (**str == '.')
	{
		flg->prc_enable = 1;
		++*str;
	}
	if (ft_isdigit(**str))
	{
		flg->precision = ft_atoi(*str);
		while (ft_isdigit(**str))
			++*str;
	}
}

static void	ft_flags_parsing(t_flags *flg, const char **str)
{
	while (ft_strchr("-+ 0#", **str))
	{
		if (**str == '-')
			flg->minus = 1;
		else if (**str == '+')
			flg->plus = 1;
		else if (**str == ' ')
			flg->space = 1;
		else if (**str == '0')
			flg->zero = 1;
		else
			flg->sharp = 1;
		++*str;
	}
	flg->space = (flg->plus == 0 && flg->space == 1);
	flg->zero = (flg->minus == 0 && flg->zero == 1);
}

t_flags	ft_get_flags(const char **str)
{
	t_flags			flg;

	ft_bzero(&flg, sizeof(t_flags));
	ft_flags_parsing(&flg, str);
	ft_get_width_precision(&flg, str);
	flg.specifier = *ft_strchr("cspdiuxX%", **str);
	return (flg);
}
