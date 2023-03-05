/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:18:37 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/06 15:23:46 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

typedef struct s_flags
{
	int		minus;
	int		plus;
	int		space;
	int		zero;
	int		sharp;
	int		width;
	int		prc_enable;
	int		precision;
	char	specifier;
}		t_flags;

typedef struct s_print_data
{
	int					left_justify;
	int					blank;
	char				*prefix;
	int					zero;
	char				specifier;
	size_t				print_length;
	char				c;
	char				*str;
	int					nbr;
	unsigned long long	hex;
}	t_print_data;

int				ft_printf(const char *last, ...);
int				parsing(const char *str, va_list ap);
int				ft_print_handler(t_print_data	pd);
int				format_handler(const char **str, va_list ap);

t_flags			ft_get_flags(const char **str);
t_print_data	ft_get_print_data(const char **str, va_list ap);

size_t			ft_pf_hexlen(unsigned long long hex);
size_t			ft_pf_nbrlen(int n, int is_signed_int);
int				ft_pf_char_fd(char c, int fd);
int				ft_pf_hex_fd(unsigned long long hex, int fd, int is_uppercase);
int				ft_pf_nbr_nosign_fd(int n, int fd, int is_signed_int);
int				ft_pf_nchar_fd(char c, int fd, size_t n);
int				ft_pf_nstr_fd(char *s, int fd, size_t n);
int				ft_pf_ptr_fd(void *ptr, int fd);
int				ft_pf_str_fd(char *s, int fd);

#endif