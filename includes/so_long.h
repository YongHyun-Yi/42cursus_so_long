
#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

# include "mlx.h"
# include "os_keycode_define.h"

typedef struct s_vec2d
{
	int x;
	int y;
}	t_vec2d;

typedef struct s_img_data
{
	void *img_ptr;
	int img_width;
	int img_height;
}	t_img_data;

typedef struct s_game_res
{
	t_img_data spr_empty;
	t_img_data spr_wall;
	t_img_data spr_collectible;
	t_img_data spr_exit;
	t_img_data spr_player1;
}	t_game_res;

typedef struct s_game_data
{
	void *mlx_ptr;
	void *win_ptr;
	int map_width;
	int map_height;
	char **map_arr;
	int remain_c;
	int move_cnt;
	t_vec2d player_pos;
	t_game_res game_res;
}	t_game_data;

#endif