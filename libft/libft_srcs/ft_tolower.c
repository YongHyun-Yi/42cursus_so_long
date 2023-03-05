/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:23:19 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/08 08:52:48 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	unsigned char	check;

	check = (unsigned char)c;
	if (check >= 'A' && check <= 'Z')
		return (c + 32);
	else
		return (c);
}
