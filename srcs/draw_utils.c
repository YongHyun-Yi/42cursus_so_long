/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:41:31 by yonghyle          #+#    #+#             */
/*   Updated: 2023/03/17 14:05:08 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_image(void *mlx_ptr, void *win_ptr, t_img_data img_data, \
t_vec2d pos)
{
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_data.img_ptr, \
	pos.x * img_data.img_width, pos.y * img_data.img_height);
}

void	draw_horizontal(t_game_data game_data, int y)
{
	t_vec2d	cur_pos;
	char	*map_hor_arr;
	int		x;

	cur_pos.y = y;
	map_hor_arr = game_data.map_arr[y];
	x = 0;
	while (x < game_data.map_width)
	{
		cur_pos.x = x;
		if (map_hor_arr[x] == '0')
			draw_image(game_data.mlx_ptr, game_data.win_ptr, \
			game_data.game_res.spr_empty, cur_pos);
		else if (map_hor_arr[x] == '1')
			draw_image(game_data.mlx_ptr, game_data.win_ptr, \
			game_data.game_res.spr_wall, cur_pos);
		else if (map_hor_arr[x] == 'C')
			draw_image(game_data.mlx_ptr, game_data.win_ptr, \
			game_data.game_res.spr_collectible, cur_pos);
		else if (map_hor_arr[x] == 'E')
			draw_image(game_data.mlx_ptr, game_data.win_ptr, \
			game_data.game_res.spr_exit, cur_pos);
		x++;
	}
}

void	draw_update(t_game_data game_data)
{
	int	y;

	y = 0;
	while (y < game_data.map_height)
	{
		draw_horizontal(game_data, y);
		y++;
	}
	draw_image(game_data.mlx_ptr, game_data.win_ptr, \
	game_data.game_res.spr_player1, game_data.player_pos);
}
