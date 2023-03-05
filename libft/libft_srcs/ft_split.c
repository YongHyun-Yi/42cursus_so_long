/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:13:09 by yonghyle          #+#    #+#             */
/*   Updated: 2023/03/02 00:17:28 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_splits(char const *s, char c)
{
	int	is_del;
	int	cnt;

	is_del = 1;
	cnt = 0;
	while (*s)
	{
		if (is_del && *s != c)
		{
			is_del = 0;
			cnt++;
		}
		else if (!is_del && *s == c)
			is_del = 1;
		s++;
	}
	return (cnt);
}

static char	*get_split_str(char const *s, char c, size_t *ori_index)
{
	int		serch_index;
	char	*split_str;

	serch_index = *ori_index;
	while (s[serch_index] != c && s[serch_index])
		serch_index++;
	split_str = ft_substr(s, *ori_index, serch_index - *ori_index);
	if (split_str)
		*ori_index += serch_index - *ori_index;
	return (split_str);
}

static void	free_splits(char **splits)
{
	char	*cur_split;
	char	**next_split;

	cur_split = *splits;
	next_split = splits + 1;
	while (cur_split)
	{
		free(cur_split);
		cur_split = *next_split;
		++next_split;
	}
	free(splits);
}

char	**ft_split(char const *s, char c)
{
	char	**splits;
	size_t	split_index;
	size_t	current_char;

	splits = (char **)calloc(((count_splits(s, c) + 1)), sizeof(char *));
	if (!splits)
		return (0);
	split_index = 0;
	current_char = 0;
	while (s[current_char])
	{
		while (s[current_char] == c && s[current_char])
			current_char++;
		if (s[current_char])
		{
			splits[split_index] = get_split_str(s, c, &current_char);
			if (!splits[split_index++])
			{
				free_splits(splits);
				return (0);
			}
		}
	}
	return (splits);
}
