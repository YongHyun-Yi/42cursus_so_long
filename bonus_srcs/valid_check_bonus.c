/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_check_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:34:08 by yonghyle          #+#    #+#             */
/*   Updated: 2023/03/17 15:06:41 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	check_valid_characters(t_game_data game_data)
{
	char	*charset;
	int		y;
	int		x;

	charset = "01CEP";
	y = 0;
	while (y < game_data.map_height)
	{
		x = 0;
		while (x < game_data.map_width)
		{
			if (ft_strchr(charset, game_data.map_arr[y][x]) == NULL)
				my_solong_error(&game_data, "Map file contains invalid \
				characters.\n");
			x++;
		}
		y++;
	}
}

void	check_rectangle(t_game_data game_data)
{
	int		y;
	size_t	len;

	len = 0;
	y = 0;
	while (y < game_data.map_height)
	{
		if (len == 0)
			len = ft_strlen(game_data.map_arr[y]) - \
			(ft_strchr(game_data.map_arr[y], '\n') > 0);
		else if (len != ft_strlen(game_data.map_arr[y]) - \
		(ft_strchr(game_data.map_arr[y], '\n') > 0))
			my_solong_error(&game_data, "Map is not rectangular.\n");
		y++;
	}
}

void	check_wall_closed(t_game_data game_data)
{
	int	y;
	int	x;

	y = 0;
	while (y < game_data.map_height)
	{
		x = 0;
		while (x < game_data.map_width)
		{
			if ((y == 0 || y == game_data.map_height - 1) || \
			(x == 0 || x == game_data.map_width - 1))
			{
				if (game_data.map_arr[y][x] != '1')
				{
					my_solong_error(&game_data, "The map is not walled.\n");
				}
			}
			x++;
		}
		y++;
	}
}

void	check_valid_objcnt(t_game_data game_data)
{
	if (get_collectible_cnt(game_data) == 0 || \
	get_exit_cnt(game_data) == 0 || get_exit_cnt(game_data) > 1 \
	|| get_player_cnt(game_data) == 0 || get_player_cnt(game_data) > 1)
		my_solong_error(&game_data, "Invalid number of objects in map.\n");
}

void	check_valid_path(t_game_data game_data, char **visit_arr, \
t_list *dfs_stack)
{
	int	y;

	y = 0;
	while (y < game_data.map_height)
	{
		visit_arr[y] = calloc(game_data.map_width, sizeof(char *));
		if (!visit_arr[y])
		{
			free_double_arr(visit_arr, game_data.map_height);
			my_solong_error(&game_data, "Failed to create \
			buffer for map file.\n");
		}
		y++;
	}
	if (!dfs_add(&dfs_stack, visit_arr, game_data.player_pos.x, \
	game_data.player_pos.y))
	{
		free_double_arr(visit_arr, game_data.map_height);
		my_solong_error(&game_data, "Failed to create buffer for map file.\n");
	}
	if (!my_dfs(game_data, visit_arr, &dfs_stack))
	{
		free_double_arr(visit_arr, game_data.map_height);
		my_solong_error(&game_data, "Map does not contain a valid path.\n");
	}
	free_double_arr(visit_arr, game_data.map_height);
}
