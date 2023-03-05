/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:33:55 by yonghyle          #+#    #+#             */
/*   Updated: 2022/11/20 19:38:33 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char const c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	int		start_index;
	int		end_index;

	start_index = 0;
	end_index = ft_strlen(s1) - 1;
	while (is_set(s1[start_index], set) && s1[start_index])
		start_index++;
	while (is_set(s1[end_index], set) && end_index >= 0)
		end_index--;
	if (end_index == -1)
		s2 = ft_strdup("");
	else
		s2 = ft_substr(s1, start_index, end_index - start_index + 1);
	return (s2);
}
