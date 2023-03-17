/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_check_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:37:23 by yonghyle          #+#    #+#             */
/*   Updated: 2023/03/17 15:06:32 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	get_collectible_cnt(t_game_data game_data)
{
	int	y;
	int	x;
	int	cnt;

	cnt = 0;
	y = 0;
	while (y < game_data.map_height)
	{
		x = 0;
		while (x < game_data.map_width)
		{
			if (game_data.map_arr[y][x] == 'C')
				cnt++;
			x++;
		}
		y++;
	}
	return (cnt);
}

int	get_exit_cnt(t_game_data game_data)
{
	int	y;
	int	x;
	int	cnt;

	cnt = 0;
	y = 0;
	while (y < game_data.map_height)
	{
		x = 0;
		while (x < game_data.map_width)
		{
			if (game_data.map_arr[y][x] == 'E')
				cnt++;
			x++;
		}
		y++;
	}
	return (cnt);
}

int	get_player_cnt(t_game_data game_data)
{
	int	y;
	int	x;
	int	cnt;

	cnt = 0;
	y = 0;
	while (y < game_data.map_height)
	{
		x = 0;
		while (x < game_data.map_width)
		{
			if (game_data.map_arr[y][x] == 'P')
				cnt++;
			x++;
		}
		y++;
	}
	return (cnt);
}

t_vec2d	get_player_pos(t_game_data game_data)
{
	t_vec2d	pos;

	pos.y = 0;
	while (pos.y < game_data.map_height)
	{
		pos.x = 0;
		while (pos.x < game_data.map_width)
		{
			if (game_data.map_arr[pos.y][pos.x] == 'P')
			{
				return (pos);
			}
			pos.x++;
		}
		pos.y++;
	}
	return (pos);
}
