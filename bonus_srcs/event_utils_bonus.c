/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:43:36 by yonghyle          #+#    #+#             */
/*   Updated: 2023/03/17 20:46:31 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	my_key_hook(int keycode, t_game_data *game_data)
{
	if (keycode == KEY_ESC)
		my_solong_exit(game_data);
	else if (keycode == KEY_W || keycode == KEY_A || \
	keycode == KEY_S || keycode == KEY_D)
		move_event(keycode, game_data);
	draw_update(*game_data);
	return (1);
}

void	move_event(int keycode, t_game_data *game_data)
{
	t_vec2d	cur_pos;

	cur_pos = game_data->player_pos;
	cur_pos.y += ((keycode == KEY_S) - (keycode == KEY_W));
	cur_pos.x += ((keycode == KEY_D) - (keycode == KEY_A));
	if (game_data->map_arr[cur_pos.y][cur_pos.x] != '1')
	{
		if (game_data->map_arr[cur_pos.y][cur_pos.x] == 'C')
		{
			game_data->map_arr[cur_pos.y][cur_pos.x] = '0';
			game_data->remain_c--;
		}
		else if (game_data->map_arr[cur_pos.y][cur_pos.x] == 'E' && \
		!game_data->remain_c)
			my_solong_exit(game_data);
		game_data->player_pos.x = cur_pos.x;
		game_data->player_pos.y = cur_pos.y;
		game_data->move_cnt++;
	}
}
