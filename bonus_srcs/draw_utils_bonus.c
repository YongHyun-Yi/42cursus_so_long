/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:41:31 by yonghyle          #+#    #+#             */
/*   Updated: 2023/03/19 01:40:20 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

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
	int			y;
	const char	*ui_text = "Move Count: ";
	char		*ui_count;

	y = 0;
	while (y < game_data.map_height)
	{
		draw_horizontal(game_data, y);
		y++;
	}
	draw_image(game_data.mlx_ptr, game_data.win_ptr, \
	game_data.game_res.spr_player[game_data.spr_frame], \
	game_data.player_pos);
	draw_image(game_data.mlx_ptr, game_data.win_ptr, \
	game_data.game_res.spr_enemy[game_data.spr_frame], \
	game_data.enemy_pos);
	mlx_string_put(game_data.mlx_ptr, game_data.win_ptr, 5, 20, \
	create_trgb(0, 255, 255, 255), (char *)ui_text);
	ui_count = ft_itoa(game_data.move_cnt);
	mlx_string_put(game_data.mlx_ptr, game_data.win_ptr, TEST_OFFSET, 20, \
	create_trgb(0, 255, 255, 255), ui_count);
	free(ui_count);
}
