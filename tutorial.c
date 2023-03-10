
#include "so_long.h"

int esc_pressed = 0;
int key_pressed = 0;
float sec = 0.0;

typedef struct	s_data
{
	void *img;
	char *addr;
	int bit_per_pixel;
	int line_length;
	int endian;
}	t_data;

typedef struct s_pos
{
	void *mlx_ptr;
	void *win_ptr;
	int	x;
	int	y;
	t_data *img;
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

int deal_mlx_key_hook(int key, void *param)
{
	ft_printf("Hello!! from mlx key hook func\n");
	return (0);
}

int deal_destroy_event(t_pos *player_pos)
{
	esc_pressed = 1;
	return (0);
}

int esc_check(t_pos *player_pos)
{
	// mlx_clear_window(player_pos->mlx_ptr, player_pos->win_ptr);
	mlx_put_image_to_window(player_pos->mlx_ptr, player_pos->win_ptr, (player_pos->img)->img, player_pos->x, player_pos->y);
	if (esc_pressed)
	{
		mlx_destroy_window(player_pos->mlx_ptr, player_pos->win_ptr);
		// mlx_destroy_display(player_pos->mlx_ptr); // Mac 버전 mlx에서는 구현되지 않은 함수
	}
	if (key_pressed)
	{
		if (sec < 5.0)
			sec += 0.00016;
		else if (sec > 5.0)
		{
			ft_printf("key press a few sec tirggered!\n");
			sec = 5.0;
		}
	}
	else if (sec)
		sec = 0.0;
	return (0);
}

int deal_key(int key, void *param)
{
	t_pos *player_pos;

	player_pos = (t_pos *)param;
	// if (key == KEY_UP) // up
	// 	player_pos->y--;
	// else if (key == KEY_DOWN) // down
	// 	player_pos->y++;
	// else if (key == KEY_LEFT) // left
	// 	player_pos->x--;
	// else if (key == KEY_RIGHT) // right
	// 	player_pos->x++;
	if (key == KEY_UP) // up
		player_pos->y -= 5;
	else if (key == KEY_DOWN) // down
		player_pos->y += 5;
	else if (key == KEY_LEFT) // left
		player_pos->x -= 5;
	else if (key == KEY_RIGHT) // right
		player_pos->x += 5;
	else if (key == KEY_ESC) // esc
		esc_pressed = 1;
	mlx_pixel_put(player_pos->mlx_ptr, player_pos->win_ptr, player_pos->x, player_pos->y, 0xFFFFFF);
	ft_printf("key code: %d\n", key);
	return (0);
}

int key_release_hook(int key, t_pos *player_pos)
{
	key_pressed = 0;
	return (0);
}

int key_press_hook(int key, t_pos *player_pos)
{
	key_pressed = 1;
	return (0);
}

int enter_hook(void *param)
{
	ft_printf("Hello!\n");
	return (0);
}

int leave_hook(void *param)
{
	ft_printf("Bye!\n");
	return (0);
}

int motion_hook(int x, int y, t_pos *player_pos)
{
	ft_printf("mouse pos\nx: %d\ny: %d\n", x, y);
	return (0);
}

void my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char *dest;

	dest = img->addr + (y * img->line_length) + (x * (img->bit_per_pixel / 8));
	*(unsigned int *)dest = color;
}

int main()
{
	void *mlx_ptr;
	void *win_ptr;
	t_pos player_pos;
	int my_color;
	t_data img;
	int img_x;
	int img_y;
	char *img_dir = "./custom.xpm";

	ft_printf("cur os: %s\n", CUR_OS);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1280, 720, "Hello World!");
	player_pos.mlx_ptr = mlx_ptr;
	player_pos.win_ptr = win_ptr;
	player_pos.x = 250;
	player_pos.y = 250;
	player_pos.img = &img;
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

	mlx_do_key_autorepeaton(player_pos.mlx_ptr);
	// mlx_do_key_autorepeatoff(player_pos.mlx_ptr);
	// mlx_key_hook(win_ptr, deal_mlx_key_hook, &player_pos);
	mlx_key_hook(win_ptr, deal_key, &player_pos);
	// mlx_hook(win_ptr, 2, 1L<<0, deal_key, &player_pos); // 누를 때
	// mlx_hook(win_ptr, 3, 1L<<1, deal_key, &player_pos); // 뗄 때
	// mlx_hook(win_ptr, 2, 1L<<0, key_press_hook, &player_pos); // 누를 때
	// mlx_hook(win_ptr, 3, 1L<<1, key_release_hook, &player_pos); // 뗄 때
	mlx_hook(win_ptr, 17, 0, deal_destroy_event, &player_pos); // 닫기버튼 누를 때
	// mlx_hook(win_ptr, 7, 1L<<4, enter_hook, &player_pos); // enter
	// mlx_hook(win_ptr, 8, 1L<<5, leave_hook, &player_pos); // leave
	// mlx_hook(win_ptr, 6, 1L<<6, motion_hook, &player_pos); // mouse motion
	mlx_loop_hook(mlx_ptr, esc_check, &player_pos);
	// mlx_loop(mlx_ptr);
	// free(mlx_ptr);

	// img.img = mlx_xpm_to_image(mlx_ptr,, &img_x, &img_y);
	img.img = mlx_xpm_file_to_image(mlx_ptr, "./custom.xpm", &img_x, &img_y);
	// img.img = mlx_new_image(mlx_ptr, 640, 360);
	// img.addr = mlx_get_data_addr(img.img, &img.bit_per_pixel, &img.line_length, &img.endian);
	// for (int j = 0; j < 360; j++)
	// {
	// 	for (int i = 0; i < 640; i++)
	// 	{
	// 		my_mlx_pixel_put(&img, i, j, create_trgb(0, 0, 180, 0));
	// 	}
	// }
	// mlx_put_image_to_window(mlx_ptr, win_ptr, img.img, 320, 180);

	my_color = create_trgb(0, 255, 255, 255);
	mlx_string_put(mlx_ptr, win_ptr, 100, 20, my_color, "This is First Text!");
	mlx_string_put(mlx_ptr, win_ptr, 100, 150, my_color, "This is Second Text!");
	mlx_loop(mlx_ptr);
	
}