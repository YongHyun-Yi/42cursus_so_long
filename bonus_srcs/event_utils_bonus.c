/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:43:36 by yonghyle          #+#    #+#             */
/*   Updated: 2023/03/18 20:08:28 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	collision_check(t_game_data *game_data)
{
	if (game_data->player_pos.x == game_data->enemy_pos.x && \
	game_data->player_pos.y == game_data->enemy_pos.y)
	{
		usleep(500000);
		my_solong_exit(game_data);
	}
}

void	enemy_move_event(t_game_data *game_data)
{
	t_vec2d	cur_pos;
	int		dir;

	while (1)
	{
		cur_pos = game_data->enemy_pos;
		dir = rand() % 4;
		cur_pos.x += (dir == 1) + ((dir == 3) * -1);
		cur_pos.y += (dir == 2) + ((dir == 0) * -1);
		if (game_data->pat_arr[cur_pos.y][cur_pos.x])
			break ;
	}
	game_data->enemy_pos.x = cur_pos.x;
	game_data->enemy_pos.y = cur_pos.y;
}

int	my_key_hook(int keycode, t_game_data *game_data)
{
	if (keycode == KEY_ESC)
		my_solong_exit(game_data);
	else if (keycode == KEY_W || keycode == KEY_A || \
	keycode == KEY_S || keycode == KEY_D)
	{
		if (move_event(keycode, game_data))
		{
			enemy_move_event(game_data);
			draw_update(*game_data);
			collision_check(game_data);
		}
	}
	return (1);
}

int	move_event(int keycode, t_game_data *game_data)
{
	t_vec2d	cur_pos;

	cur_pos = game_data->player_pos;
	cur_pos.y += ((keycode == KEY_S) - (keycode == KEY_W));
	cur_pos.x += ((keycode == KEY_D) - (keycode == KEY_A));
	if (game_data->map_arr[cur_pos.y][cur_pos.x] == '1')
		return (0);
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
	game_data->spr_frame++;
	game_data->spr_frame %= 2;
	return (1);
}
