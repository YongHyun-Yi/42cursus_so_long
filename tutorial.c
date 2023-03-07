
#include "so_long.h"
#include "mlx.h"

typedef struct s_pos
{
	void *mlx_ptr;
	void *win_ptr;
	int	x;
	int	y;
}	t_pos;

int deal_key(int key, void *param)
{
	t_pos *player_pos;

	player_pos = (t_pos *)param;
	if (key == 65362) // up
		player_pos->y--;
	else if (key == 65364) // down
		player_pos->y++;
	else if (key == 65361) // left
		player_pos->x--;
	else if (key == 65363) // right
		player_pos->x++;
	mlx_pixel_put(player_pos->mlx_ptr, player_pos->win_ptr, player_pos->x, player_pos->y, 0xFFFFFF);
	ft_printf("key code: %d\n", key);
	return (0);
}

int main()
{
	void *mlx_ptr;
	void *win_ptr;
	t_pos player_pos;

	ft_printf("cur os: %s\n", CUR_OS);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "mlx 42");
	player_pos.mlx_ptr = mlx_ptr;
	player_pos.win_ptr = win_ptr;
	player_pos.x = 250;
	player_pos.y = 250;
	mlx_pixel_put(mlx_ptr, win_ptr, player_pos.x, player_pos.y, 0xFFFFFF);
	mlx_key_hook(win_ptr, deal_key, &player_pos);
	mlx_loop(mlx_ptr);
}