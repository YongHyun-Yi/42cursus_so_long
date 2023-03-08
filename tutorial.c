
#include "so_long.h"

typedef struct s_pos
{
	void *mlx_ptr;
	void *win_ptr;
	int	x;
	int	y;
}	t_pos;

int create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int get_t(int trgb)
{
	return ((trgb >> 24) & 255);
}

int get_r(int trgb)
{
	return ((trgb >> 16) & 255);
}

int get_g(int trgb)
{
	return ((trgb >> 8) & 255);
}

int get_b(int trgb)
{
	return (trgb & 255);
}

int add_shade(double distance, int trgb)
{
	int t = get_t(trgb);
	int r = get_r(trgb);
	int g = get_g(trgb);
	int b = get_b(trgb);

	r -= distance * r;
	g -= distance * g;
	b -= distance * b;

	return (t << 24 | r << 16 | g << 8 | b);
}

int get_opposite(int trgb)
{
	int t = get_t(trgb);
	int r = get_r(trgb);
	int g = get_g(trgb);
	int b = get_b(trgb);

	r = 255 - r;
	g = 255 - g;
	b = 255 - b;

	return (t << 24 | r << 16 | g << 8 | b);
}

int deal_key(int key, void *param)
{
	t_pos *player_pos;

	player_pos = (t_pos *)param;
	if (key == KEY_UP) // up
		player_pos->y--;
	else if (key == KEY_DOWN) // down
		player_pos->y++;
	else if (key == KEY_LEFT) // left
		player_pos->x--;
	else if (key == KEY_RIGHT) // right
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
	int my_color;

	ft_printf("cur os: %s\n", CUR_OS);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "mlx 42");
	player_pos.mlx_ptr = mlx_ptr;
	player_pos.win_ptr = win_ptr;
	player_pos.x = 250;
	player_pos.y = 250;
	mlx_pixel_put(mlx_ptr, win_ptr, player_pos.x, player_pos.y, 0xFFFFFF);

	my_color = create_trgb(0, 0, 255, 0);
	for (int j = 100; j < 150; j++)
	{
		for (int i = 200; i < 300; i++)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, i, j, my_color);
		}
	}
	my_color = get_opposite(my_color);
	for (int j = 150; j < 200; j++)
	{
		for (int i = 200; i < 300; i++)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, i, j, my_color);
		}
	}
	// 보색 표현

	double dis = 0.0;
	my_color = create_trgb(0, 0, 255, 0);
	for (int j = 300; j < 400; j++)
	{
		for (int i = 200; i < 300; i++)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, i, j, my_color);
		}
		dis += 0.0005;
		my_color = add_shade(dis, my_color);
	}
	// 음영 표현

	mlx_key_hook(win_ptr, deal_key, &player_pos);
	mlx_loop(mlx_ptr);
}