/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 23:10:27 by yonghyle          #+#    #+#             */
/*   Updated: 2023/03/19 00:37:34 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	get_area_width(char *pat_arr, int start_x)
{
	int	width;

	width = 0;
	while (pat_arr[start_x++])
		width++;
	return (width);
}

int	get_area_height(char **pat_arr, int start_x, int start_y)
{
	int	height;
	int	width;
	int	width_max;

	width_max = 0;
	height = 0;
	while (1)
	{
		width = get_area_width(pat_arr[start_y++], start_x);
		if (width_max == 0)
			width_max = width;
		if (width == 0 || width < width_max)
			break ;
		height++;
	}
	return (height);
}

int	get_area_size(char **pat_arr, int start_x, int start_y)
{
	return (get_area_width(pat_arr[start_y], start_x) * \
	get_area_height(pat_arr, start_x, start_y));
}

void	get_largest_area_pos(t_game_data game_data, t_vec2d	*area_pos)
{
	t_vec2d	iter;
	int		max_size;

	max_size = 0;
	iter.y = 0;
	while (iter.y < game_data.map_height)
	{
		iter.x = 0;
		while (iter.x < game_data.map_width)
		{
			if (get_area_size(game_data.pat_arr, iter.x, iter.y) > max_size)
			{
				max_size = get_area_size(game_data.pat_arr, iter.x, iter.y);
				area_pos->x = iter.x;
				area_pos->y = iter.y;
			}
			iter.x++;
		}
		iter.y++;
	}
}
