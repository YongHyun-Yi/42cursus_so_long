/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:34:40 by yonghyle          #+#    #+#             */
/*   Updated: 2023/03/17 11:33:08 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_double_arr(char **arr, size_t n)
{
	size_t	idx;

	idx = 0;
	while (idx < n && arr[idx])
		free(arr[idx++]);
	free(arr);
}

void free_game_res(void *mlx_ptr, t_game_res *game_res)
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

int load_xmp_file(void *mlx_ptr, t_img_data *img_data, char *path)
{
	img_data->img_ptr = mlx_xpm_file_to_image(mlx_ptr, path, &img_data->img_width, &img_data->img_height);
	if (!img_data->img_ptr)
		return (0);
	return (1);
}

void load_game_res(t_game_data *game_data)
{
	void *mlx_ptr;
	t_game_res *game_res;

	mlx_ptr = game_data->mlx_ptr;
	game_res = &game_data->game_res;
	if (!load_xmp_file(mlx_ptr, &game_res->spr_empty, "./res/sprite/empty_space.xpm") || \
	!load_xmp_file(mlx_ptr, &game_res->spr_wall, "./res/sprite/wall.xpm") || \
	!load_xmp_file(mlx_ptr, &game_res->spr_collectible, "./res/sprite/collectible.xpm") || \
	!load_xmp_file(mlx_ptr, &game_res->spr_exit, "./res/sprite/exit.xpm") || \
	!load_xmp_file(mlx_ptr, &game_res->spr_player1, "./res/sprite/player1.xpm"))
	my_solong_error(game_data, "Failed to load game resources.\n");
}

t_vec2d get_player_pos(t_game_data game_data)
{
	t_vec2d pos;

	pos.y = 0;
	while (pos.y < game_data.map_height)
	{
		pos.x = 0;
		while (pos.x < game_data.map_width)
		{
			if (game_data.map_arr[pos.y][pos.x] == 'P')
			{
				return (pos);
			}
			pos.x++;
		}
		pos.y++;
	}
	return (pos);
}

void draw_image(void *mlx_ptr, void *win_ptr, t_img_data img_data, t_vec2d pos)
{
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_data.img_ptr, pos.x * img_data.img_width, pos.y * img_data.img_height);
}

void draw_horizontal(t_game_data game_data, int y)
{
	t_vec2d cur_pos;
	char *map_hor_arr;
	int x;

	cur_pos.y = y;
	map_hor_arr = game_data.map_arr[y];
	x = 0;
	while (x < game_data.map_width)
	{
		cur_pos.x = x;
		if (map_hor_arr[x] == '0')
			draw_image(game_data.mlx_ptr, game_data.win_ptr, game_data.game_res.spr_empty, cur_pos);
		else if (map_hor_arr[x] == '1')
			draw_image(game_data.mlx_ptr, game_data.win_ptr, game_data.game_res.spr_wall, cur_pos);
		else if (map_hor_arr[x] == 'C')
			draw_image(game_data.mlx_ptr, game_data.win_ptr, game_data.game_res.spr_collectible, cur_pos);
		else if (map_hor_arr[x] == 'E')
			draw_image(game_data.mlx_ptr, game_data.win_ptr, game_data.game_res.spr_exit, cur_pos);
		x++;
	}
}

void draw_update(t_game_data game_data)
{
	int y;
	y = 0;
	while (y < game_data.map_height)
	{
		draw_horizontal(game_data, y);
		y++;
	}
	draw_image(game_data.mlx_ptr, game_data.win_ptr, game_data.game_res.spr_player1, game_data.player_pos);
}

void check_valid_characters(t_game_data game_data)
{
	char *charset;
	int y;
	int x;

	charset = "01CEP";
	y = 0;
	while (y < game_data.map_height)
	{
		x = 0;
		while (x < game_data.map_width)
		{
			if (ft_strchr(charset, game_data.map_arr[y][x]) == NULL)
				my_solong_error(&game_data, "Map file contains invalid characters.\n");
			x++;
		}
		y++;
	}
}

void check_rectangle(t_game_data game_data)
{
	int y;
	size_t len;

	len = 0;
	y = 0;
	while (y < game_data.map_height)
	{
		if (len == 0)
			len = ft_strlen(game_data.map_arr[y]) - (ft_strchr(game_data.map_arr[y], '\n') > 0);
		else if (len != ft_strlen(game_data.map_arr[y]) - (ft_strchr(game_data.map_arr[y], '\n') > 0))
			my_solong_error(&game_data, "Map is not rectangular.\n");
		y++;
	}
}

void check_wall_closed(t_game_data game_data)
{
	int y;
	int x;

	y = 0;
	while (y < game_data.map_height)
	{
		x = 0;
		while (x < game_data.map_width)
		{
			if ((y == 0 || y == game_data.map_height - 1) || (x == 0 || x == game_data.map_width - 1))
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

int get_collectible_cnt(t_game_data game_data)
{
	int y;
	int x;
	int cnt;

	cnt = 0;
	y = 0;
	while (y < game_data.map_height)
	{
		x = 0;
		while (x < game_data.map_width)
		{
			if (game_data.map_arr[y][x] == 'C')
				cnt++;
			x++;
		}
		y++;
	}
	return (cnt);
}

int get_exit_cnt(t_game_data game_data)
{
	int y;
	int x;
	int cnt;

	cnt = 0;
	y = 0;
	while (y < game_data.map_height)
	{
		x = 0;
		while (x < game_data.map_width)
		{
			if (game_data.map_arr[y][x] == 'E')
				cnt++;
			x++;
		}
		y++;
	}
	return (cnt);
}

int get_player_cnt(t_game_data game_data)
{
	int y;
	int x;
	int cnt;

	cnt = 0;
	y = 0;
	while (y < game_data.map_height)
	{
		x = 0;
		while (x < game_data.map_width)
		{
			if (game_data.map_arr[y][x] == 'P')
				cnt++;
			x++;
		}
		y++;
	}
	return (cnt);
}

void check_valid_objcnt(t_game_data game_data)
{
	if (get_collectible_cnt(game_data) == 0 || get_exit_cnt(game_data) == 0 || get_exit_cnt(game_data) > 1 || get_player_cnt(game_data) == 0 || get_player_cnt(game_data) > 1)
		my_solong_error(&game_data, "Invalid number of objects in map.\n");
}

int dfs_add(t_list **dfs_stack, char **visit_arr, int x, int y)
{
	t_list *new_node;
	t_vec2d *new_pos;

	visit_arr[y][x] = 1;
	new_pos = (t_vec2d *)malloc(sizeof(t_vec2d));
	if (!new_pos)
		return (0);
	new_pos->x = x;
	new_pos->y = y;
	new_node = ft_lstnew(new_pos);
	if (!new_node)
		return (0);
	ft_lstadd_back(dfs_stack, new_node);
	return (1);
}

int dfs_check(t_game_data game_data, char **visit_arr, int x, int y)
{
	if (x >= 0 && x < game_data.map_width && y >= 0 && y < game_data.map_height)
	{
		if (game_data.map_arr[y][x] != '1' && !visit_arr[y][x])
			return (1);
	}
	return (0);
}

int dfs_check_4dir(t_game_data game_data, char **visit_arr, t_list **dfs_stack, t_vec2d *cur_pos)
{
	// 해당 좌표로 추가하고 visit_arr 업데이트
	if (dfs_check(game_data, visit_arr, cur_pos->x - 1, cur_pos->y))
	{
		if (!dfs_add(dfs_stack, visit_arr, cur_pos->x - 1, cur_pos->y))
			return (0);
	}
	if (dfs_check(game_data, visit_arr, cur_pos->x + 1, cur_pos->y))
	{
		if (!dfs_add(dfs_stack, visit_arr, cur_pos->x + 1, cur_pos->y))
			return (0);
	}
	if (dfs_check(game_data, visit_arr, cur_pos->x, cur_pos->y - 1))
	{
		if (!dfs_add(dfs_stack, visit_arr, cur_pos->x, cur_pos->y - 1))
			return (0);
	}
	if (dfs_check(game_data, visit_arr, cur_pos->x, cur_pos->y + 1))
	{
		if (!dfs_add(dfs_stack, visit_arr, cur_pos->x, cur_pos->y + 1))
			return (0);
	}
	return (1);
}

int my_dfs(t_game_data game_data, char **visit_arr, t_list **dfs_stack)
{
	t_list *cur_node;
	t_vec2d *cur_pos;
	size_t can_exit;
	size_t remain_c;

	can_exit = 0;
	remain_c = game_data.remain_c;
	while (*dfs_stack)
	{
		cur_node = ft_lstlast(*dfs_stack);
		cur_pos = (t_vec2d *)(cur_node->content);
		if (game_data.map_arr[cur_pos->y][cur_pos->x] == 'E')
			can_exit++;
		else if (game_data.map_arr[cur_pos->y][cur_pos->x] == 'C')
			remain_c--;
		if (!dfs_check_4dir(game_data, visit_arr, dfs_stack, cur_node->content))
			break ;
		ft_lstdel_node(dfs_stack, cur_node, free);
	}
	ft_lstclear(dfs_stack, free);
	if (remain_c || !can_exit)
		return (0);
	return (1);
}

void check_valid_path(t_game_data game_data, char **visit_arr, t_list *dfs_stack)
{
	int y;

	y = 0;
	while (y < game_data.map_height)
	{
		visit_arr[y] = calloc(game_data.map_width, sizeof(char *));
		if (!visit_arr[y])
		{
			free_double_arr(visit_arr, game_data.map_height);
			my_solong_error(&game_data, "Failed to create buffer for map file.\n");
		}
		y++;
	}
	if (!dfs_add(&dfs_stack, visit_arr, game_data.player_pos.x, game_data.player_pos.y))
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

void map_arr_check(t_game_data *game_data)
{
	char **visit_arr;
	t_list *dfs_stack;

	check_valid_characters(*game_data);
	check_rectangle(*game_data);
	check_wall_closed(*game_data);
	check_valid_objcnt(*game_data);
	game_data->remain_c = get_collectible_cnt(*game_data);
	game_data->player_pos = get_player_pos(*game_data);
	game_data->map_arr[game_data->player_pos.y][game_data->player_pos.x] = '0';
	visit_arr = (char **)calloc(game_data->map_height, sizeof(char *));
	if (!visit_arr)
		my_solong_error(game_data, "Failed to create buffer for map file.\n");
	dfs_stack = NULL;
	check_valid_path(*game_data, visit_arr, dfs_stack);
}

void move_event(int keycode, t_game_data *game_data)
{
	t_vec2d cur_pos;

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
		else if (game_data->map_arr[cur_pos.y][cur_pos.x] == 'E' && !game_data->remain_c)
			my_solong_exit(game_data);
		game_data->player_pos.x = cur_pos.x;
		game_data->player_pos.y = cur_pos.y;
		ft_printf("Move Count: %d\n", ++(game_data->move_cnt));
	}
}

int my_key_hook(int keycode, t_game_data *game_data)
{
	if (keycode == KEY_ESC)
		my_solong_exit(game_data);
	else if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_S || keycode == KEY_D)
		move_event(keycode, game_data);
	draw_update(*game_data);
	return(1);
}

t_list *gnl_to_list(char *map_file_path, t_game_data *game_data)
{
	int fd;
	t_list *map_list;
	t_list *new_node;
	char *gnl;

	fd = open(map_file_path, O_RDONLY);
	if (fd < 0)
		my_solong_error(game_data, "Cannot open file.\n");
	map_list = NULL;
	gnl = get_next_line(fd);
	while (gnl)
	{
		new_node = ft_lstnew(gnl);
		if (!new_node)
		{
			ft_lstclear(&map_list, free);
			close(fd);
			my_solong_error(game_data, "Failed to create buffer for map file.\n");
		}
		ft_lstadd_back(&map_list, new_node);
		game_data->map_height++;
		gnl = get_next_line(fd);
	}
	close(fd);
	return (map_list);
}

void list_to_map_arr(t_list *map_list, t_game_data *game_data)
{
	t_list *list_iter;
	int i;

	i = 0;
	list_iter = map_list;
	game_data->map_arr = (char **)malloc(sizeof(char *) * game_data->map_height);
	if (!game_data->map_arr)
	{
		ft_lstclear(&map_list, free);
		my_solong_error(game_data, "Failed to create buffer for map file.\n");
	}
	while (list_iter)
	{
		game_data->map_arr[i] = list_iter->content;
		list_iter = list_iter->next;
		i++;
	}
	ft_lstclear(&map_list, NULL);
}

void leakcheck()
{
	system("leaks so_long");
}

int main(int argc, char *argv[])
{
	t_game_data game_data;

	atexit(leakcheck);
	ft_bzero(&game_data, sizeof(t_game_data));
	if (argc != 2)
		my_solong_error(&game_data, "The program was given invalid arguments.\n");
	if (ft_strlen(argv[1]) < 4 || ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".ber", 4))
		my_solong_error(&game_data, "Invalid extension of file.\n");
	list_to_map_arr(gnl_to_list(argv[1], &game_data), &game_data);
	game_data.map_width = ft_strlen(game_data.map_arr[0]) - (ft_strchr(game_data.map_arr[0], '\n') > 0);
	map_arr_check(&game_data);
	game_data.mlx_ptr = mlx_init();
	game_data.win_ptr = mlx_new_window(game_data.mlx_ptr, game_data.map_width * 32, game_data.map_height * 32, "so_long");
	load_game_res(&game_data);
	draw_update(game_data);
	mlx_key_hook(game_data.win_ptr, my_key_hook, &game_data);
	mlx_hook(game_data.win_ptr, 17, 0, my_solong_exit, &game_data);
	mlx_loop(game_data.mlx_ptr);
}