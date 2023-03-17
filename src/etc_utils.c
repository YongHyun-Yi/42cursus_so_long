/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:40:47 by yonghyle          #+#    #+#             */
/*   Updated: 2023/03/17 13:41:18 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int my_solong_exit(t_game_data *game_data)
{
	if (game_data->map_arr)
		free_double_arr(game_data->map_arr, game_data->map_height);
	free_game_res(game_data->mlx_ptr, &game_data->game_res);
	if (game_data->win_ptr)
		mlx_destroy_window(game_data->mlx_ptr, game_data->win_ptr);
	exit(EXIT_SUCCESS);
}

void my_solong_error(t_game_data *game_data, char *err_msg)
{
	if (game_data->map_arr)
		free_double_arr(game_data->map_arr, game_data->map_height);
	free_game_res(game_data->mlx_ptr, &game_data->game_res);
	if (game_data->win_ptr)
		mlx_destroy_window(game_data->mlx_ptr, game_data->win_ptr);
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	free_double_arr(char **arr, size_t n)
{
	size_t	idx;

	idx = 0;
	while (idx < n && arr[idx])
		free(arr[idx++]);
	free(arr);
}
