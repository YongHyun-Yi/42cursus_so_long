/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:08:18 by yonghyle          #+#    #+#             */
/*   Updated: 2023/03/17 21:02:48 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

# include "mlx.h"
# include "os_keycode_define.h"

typedef struct s_vec2d
{
	int	x;
	int	y;
}	t_vec2d;

typedef struct s_img_data
{
	void	*img_ptr;
	int		img_width;
	int		img_height;
}	t_img_data;

typedef struct s_game_res
{
	t_img_data	spr_empty;
	t_img_data	spr_wall;
	t_img_data	spr_collectible;
	t_img_data	spr_exit;
	t_img_data	spr_player1;
}	t_game_res;

typedef struct s_game_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			map_width;
	int			map_height;
	char		**map_arr;
	int			remain_c;
	int			move_cnt;
	id_t		spr_frame;
	t_vec2d		player_pos;
	t_game_res	game_res;
}	t_game_data;

t_list	*gnl_to_list(char *map_file_path, t_game_data *game_data);
void	list_to_map_arr(t_list *map_list, t_game_data *game_data);
void	map_arr_check(t_game_data *game_data);

void	check_valid_characters(t_game_data game_data);
void	check_rectangle(t_game_data game_data);
void	check_wall_closed(t_game_data game_data);
void	check_valid_objcnt(t_game_data game_data);
void	check_valid_path(t_game_data game_data, char **visit_arr, \
t_list *dfs_stack);

int		get_collectible_cnt(t_game_data game_data);
int		get_exit_cnt(t_game_data game_data);
int		get_player_cnt(t_game_data game_data);
t_vec2d	get_player_pos(t_game_data game_data);

int		my_dfs(t_game_data game_data, char **visit_arr, t_list **dfs_stack);
int		dfs_add(t_list **dfs_stack, char **visit_arr, int x, int y);
int		dfs_check(t_game_data game_data, char **visit_arr, int x, int y);
void	dfs_check_horizontal(t_game_data game_data, char **visit_arr, \
t_list **dfs_stack, t_vec2d *cur_pos);
void	dfs_check_vertical(t_game_data game_data, char **visit_arr, \
t_list **dfs_stack, t_vec2d *cur_pos);

void	draw_image(void *mlx_ptr, void *win_ptr, t_img_data img_data, \
t_vec2d pos);
void	draw_horizontal(t_game_data game_data, int y);
void	draw_update(t_game_data game_data);

void	load_game_res(t_game_data *game_data);
void	free_game_res(void *mlx_ptr, t_game_res *game_res);
int		load_xmp_file(void *mlx_ptr, t_img_data *img_data, char *path);

int		my_key_hook(int keycode, t_game_data *game_data);
void	move_event(int keycode, t_game_data *game_data);

int		my_solong_exit(t_game_data *game_data);
void	my_solong_error(t_game_data *game_data, char *err_msg);
void	free_double_arr(char **arr, size_t n);

#endif