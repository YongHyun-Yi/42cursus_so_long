/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:16:45 by yonghyle          #+#    #+#             */
/*   Updated: 2022/11/14 13:24:32 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	unsigned char	check;

	check = (unsigned char)c;
	if (check >= 'a' && check <= 'z')
		return (c - 32);
	else
		return (c);
}
