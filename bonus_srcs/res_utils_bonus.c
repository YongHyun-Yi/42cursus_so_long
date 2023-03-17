/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   res_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:42:23 by yonghyle          #+#    #+#             */
/*   Updated: 2023/03/17 15:06:02 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	load_game_res(t_game_data *game_data)
{
	void		*mlx_ptr;
	t_game_res	*game_res;

	mlx_ptr = game_data->mlx_ptr;
	game_res = &game_data->game_res;
	if (!load_xmp_file(mlx_ptr, &game_res->spr_empty, \
	"./res/sprite/empty_space.xpm") || !load_xmp_file(mlx_ptr, \
	&game_res->spr_wall, "./res/sprite/wall.xpm") || \
	!load_xmp_file(mlx_ptr, &game_res->spr_collectible, \
	"./res/sprite/collectible.xpm") || !load_xmp_file(mlx_ptr, \
	&game_res->spr_exit, "./res/sprite/exit.xpm") || \
	!load_xmp_file(mlx_ptr, &game_res->spr_player1, "./res/sprite/player1.xpm"))
		my_solong_error(game_data, "Failed to load game resources.\n");
}

void	free_game_res(void *mlx_ptr, t_game_res *game_res)
{
	if ((game_res->spr_empty).img_ptr)
		mlx_destroy_image(mlx_ptr, (game_res->spr_empty).img_ptr);
	if ((game_res->spr_wall).img_ptr)
		mlx_destroy_image(mlx_ptr, (game_res->spr_wall).img_ptr);
	if ((game_res->spr_collectible).img_ptr)
		mlx_destroy_image(mlx_ptr, (game_res->spr_collectible).img_ptr);
	if ((game_res->spr_exit).img_ptr)
		mlx_destroy_image(mlx_ptr, (game_res->spr_exit).img_ptr);
	if ((game_res->spr_player1).img_ptr)
		mlx_destroy_image(mlx_ptr, (game_res->spr_player1).img_ptr);
}

int	load_xmp_file(void *mlx_ptr, t_img_data *img_data, char *path)
{
	img_data->img_ptr = mlx_xpm_file_to_image(mlx_ptr, path, \
	&img_data->img_width, &img_data->img_height);
	if (!img_data->img_ptr)
		return (0);
	return (1);
}
