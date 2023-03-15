/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:34:40 by yonghyle          #+#    #+#             */
/*   Updated: 2023/03/15 12:28:06 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
// #include "../mlx_linux/mlx.h"

// 파싱 함수
// gnl을 리스트에 저장한다
// gnl로 읽어온 문자열에서 유효하지 않은 문자가 있는지 체크한다
// gnl로 읽어온 문자열이 직사각형인지 체크한다
// 이증배열 사이즈가될 map_height를 증가시킨다
// 이중배열로 옮겨담는다
// 오브젝트 갯수를 센다 (여기서 플레이어 위치를 설정)
// 플레이어 위치를 기반으로 DFS 수행
// 전부 통과하면 draw update 한번 수행후 loop 진행
//
// event_hook 함수
// 현재 플레이어 위치를 기준으로 이동가능한지 체크
// 이동가능하면 배열을 변경시킴
// 수집품이라면 수집품갯수를 줄임
// 출구라면 수집품갯수에 따라 조건분기

int load_xmp_file(void *mlx_ptr, t_img_data *img_data, char *path)
{
	img_data->img_ptr = mlx_xpm_file_to_image(mlx_ptr, path, &img_data->img_width, &img_data->img_height);
	if (!img_data->img_ptr)
		return (0);
	return (1);
}

int load_game_res(void *mlx_ptr, t_game_res *game_res)
{
	if (!load_xmp_file(mlx_ptr, &game_res->spr_empty, "./res/sprite/empty_space.xpm"))
		return (0);
	if (!load_xmp_file(mlx_ptr, &game_res->spr_wall, "./res/sprite/wall.xpm"))
		return (0);
	if (!load_xmp_file(mlx_ptr, &game_res->spr_collectible, "./res/sprite/collectible.xpm"))
		return (0);
	if (!load_xmp_file(mlx_ptr, &game_res->spr_exit, "./res/sprite/exit.xpm"))
		return (0);
	if (!load_xmp_file(mlx_ptr, &game_res->spr_player1, "./res/sprite/player1.xpm"))
		return (0);
	return (1);
}

t_vec2d *get_player_pos(t_game_data game_data)
{
	int y;
	int x;
	t_vec2d *pos;

	pos = (t_vec2d *)malloc(sizeof(t_vec2d));
	y = 0;
	while (y < game_data.map_height)
	{
		x = 0;
		while (x < game_data.map_width)
		{
			if (game_data.map_arr[y][x] == 'P')
			{
				pos->x = x;
				pos->y = y;
				return (pos);
			}
			x++;
		}
		y++;
	}
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
		else if (map_hor_arr[x] == 'P')
			draw_image(game_data.mlx_ptr, game_data.win_ptr, game_data.game_res.spr_player1, cur_pos);
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
}

int is_valid_characters(t_game_data game_data)
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
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int is_rectangle(t_game_data game_data)
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
			return (0);
		y++;
	}
	return (1);
}

int is_wall_closed(t_game_data game_data)
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
					return (0);
				}
			}
			x++;
		}
		y++;
	}
	return (1);
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

int is_valid_objcnt(t_game_data game_data)
{
	if (get_collectible_cnt(game_data) == 0 || get_exit_cnt(game_data) == 0 || get_exit_cnt(game_data) > 1 || get_player_cnt(game_data) == 0 || get_player_cnt(game_data) > 1)
		return (0);
	return (1);
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
		if ((game_data.map_arr[y][x] != '1' || game_data.map_arr[y][x] != 'E') && !visit_arr[y][x])
			return (1);
	}
	return (0);
}

// dfs_loop

int my_dfs(t_game_data game_data, char **visit_arr, char **map_arr, t_list **dfs_stack)
{
	t_list *cur_node;
	t_vec2d *cur_pos;
	t_list *new_node;
	t_vec2d *new_pos;
	size_t can_exit;
	size_t remain_c;

	can_exit = 0;
	remain_c = game_data.remain_c;
	while (*dfs_stack)
	{
		cur_node = ft_lstlast(*dfs_stack);
		cur_pos = (t_vec2d *)(cur_node->content);
		ft_lstdel_node(dfs_stack, cur_node, NULL);
		if (map_arr[cur_pos->y][cur_pos->x] == 'E')
			can_exit++;
		else if (map_arr[cur_pos->y][cur_pos->x] == 'C')
			remain_c--;
		// pop back
		// if (cur_pos->x - 1 >= 0 && map_arr[cur_pos->y][cur_pos->x - 1] != '1' && !visit_arr[cur_pos->y][cur_pos->x - 1])
		// {
		// 	visit_arr[cur_pos->y][cur_pos->x - 1] = 1;
		// 	new_pos = (t_vec2d *)malloc(sizeof(t_vec2d));
		// 	new_pos->x = cur_pos->x - 1;
		// 	new_pos->y = cur_pos->y;
		// 	new_node = ft_lstnew(new_pos);
		// 	ft_lstadd_back(&dfs_stack, new_node);
		// }
		// if (cur_pos->x + 1 < game_data.map_width && map_arr[cur_pos->y][cur_pos->x + 1] != '1' && !visit_arr[cur_pos->y][cur_pos->x + 1])
		// {
		// 	visit_arr[cur_pos->y][cur_pos->x + 1] = 1;
		// 	new_pos = (t_vec2d *)malloc(sizeof(t_vec2d));
		// 	new_pos->x = cur_pos->x + 1;
		// 	new_pos->y = cur_pos->y;
		// 	new_node = ft_lstnew(new_pos);
		// 	ft_lstadd_back(&dfs_stack, new_node);
		// }
		// if (cur_pos->y - 1 >= 0 && map_arr[cur_pos->y - 1][cur_pos->x] != '1' && !visit_arr[cur_pos->y - 1][cur_pos->x])
		// {
		// 	visit_arr[cur_pos->y - 1][cur_pos->x] = 1;
		// 	new_pos = (t_vec2d *)malloc(sizeof(t_vec2d));
		// 	new_pos->x = cur_pos->x;
		// 	new_pos->y = cur_pos->y - 1;
		// 	new_node = ft_lstnew(new_pos);
		// 	ft_lstadd_back(&dfs_stack, new_node);
		// }
		// if (cur_pos->y + 1 < game_data.map_height && map_arr[cur_pos->y + 1][cur_pos->x] != '1' && !visit_arr[cur_pos->y + 1][cur_pos->x])
		// {
		// 	visit_arr[cur_pos->y + 1][cur_pos->x] = 1;
		// 	new_pos = (t_vec2d *)malloc(sizeof(t_vec2d));
		// 	new_pos->x = cur_pos->x;
		// 	new_pos->y = cur_pos->y + 1;
		// 	new_node = ft_lstnew(new_pos);
		// 	ft_lstadd_back(&dfs_stack, new_node);
		// }
		// // 4방향체크
		// // visit 마킹후 stack에 추가

		// check 4 direction
		if (dfs_check(game_data, visit_arr, cur_pos->x - 1, cur_pos->y))
			dfs_add(dfs_stack, visit_arr, cur_pos->x - 1, cur_pos->y);
			// 해당 좌표로 추가하고 visit_arr 업데이트
		if (dfs_check(game_data, visit_arr, cur_pos->x + 1, cur_pos->y))
			dfs_add(dfs_stack, visit_arr, cur_pos->x + 1, cur_pos->y);
		if (dfs_check(game_data, visit_arr, cur_pos->x, cur_pos->y - 1))
			dfs_add(dfs_stack, visit_arr, cur_pos->x, cur_pos->y - 1);
		if (dfs_check(game_data, visit_arr, cur_pos->x, cur_pos->y + 1))
			dfs_add(dfs_stack, visit_arr, cur_pos->x, cur_pos->y + 1);
	}
	// collectible 갯수와 can exit 여부 체크
	if (remain_c || !can_exit)
		return (0);
	return (1);

	
}

int is_valid_path(t_game_data game_data)
{
	char **visit_arr;
	int y;
	t_list *dfs_stack;
	t_vec2d *player_pos;
	t_list *new;

	visit_arr = (char **)malloc(sizeof(char *) * game_data.map_height);
	y = 0;
	while (y < game_data.map_height)
		visit_arr[y++] = ft_calloc(game_data.map_width, sizeof(char));
	dfs_stack = NULL;
	player_pos = get_player_pos(game_data);
	new = ft_lstnew(player_pos);
	if (!new)
	{
		free(player_pos);
		return (0);
	}
	ft_lstadd_back(&dfs_stack, new);
	visit_arr[player_pos->y][player_pos->x] = 1;
	return (my_dfs(game_data, visit_arr, game_data.map_arr, &dfs_stack));
}

t_list *gnl_to_list(char *map_file_path, int *map_width, int *map_height)
{
	int fd;
	t_list *map_list;
	t_list *new_node;
	char *gnl;

	fd = open(map_file_path, O_RDONLY);
	if (fd < 0)
		return (0);
	map_list = NULL;
	gnl = get_next_line(fd);
	while (gnl)
	{
		new_node = ft_lstnew(gnl);
		if (!new_node)
		{
			ft_lstclear(&map_list, free);
			close(fd);
			return (0);
		}
		ft_lstadd_back(&map_list, new_node);
		(*map_height)++;
		gnl = get_next_line(fd);
	}
	close(fd);
	return (map_list);
}

int list_to_map_arr(t_list *map_list, t_game_data *game_data)
{
	t_list *list_iter;
	int i;

	i = 0;
	list_iter = map_list;
	game_data->map_arr = (char **)malloc(sizeof(char *) * game_data->map_height);
	if (!game_data->map_arr)
		return (0);
	while (list_iter)
	{
		game_data->map_arr[i] = list_iter->content;
		list_iter = list_iter->next;
		i++;
	}
	ft_lstclear(&map_list, NULL);
	return (1);
}

int map_arr_check(t_game_data *game_data)
{
	is_valid_characters(*game_data); // character check
	
	is_rectangle(*game_data); // rectangle check
	
	is_wall_closed(*game_data); // wall closed check
	
	is_valid_objcnt(*game_data); // object count check
	game_data->remain_c = get_collectible_cnt(*game_data);

	ft_printf("DFS: %d\n",is_valid_path(*game_data)); // DFS check
	
	return (1);
}

int my_key_hook(int keycode, t_game_data *game_data)
{
	t_vec2d *cur_pos;

	cur_pos = get_player_pos(*game_data);
	if (keycode == KEY_W)
	{
		if (game_data->map_arr[cur_pos->y - 1][cur_pos->x] != '1')
		{
			game_data->map_arr[cur_pos->y][cur_pos->x] = '0';
			game_data->map_arr[cur_pos->y - 1][cur_pos->x] = 'P';
		}
	}
	else if (keycode == KEY_A)
	{
		if (game_data->map_arr[cur_pos->y][cur_pos->x - 1] != '1')
		{
			game_data->map_arr[cur_pos->y][cur_pos->x] = '0';
			game_data->map_arr[cur_pos->y][cur_pos->x - 1] = 'P';
		}
	}
	else if (keycode == KEY_S)
	{
		if (game_data->map_arr[cur_pos->y + 1][cur_pos->x] != '1')
		{
			game_data->map_arr[cur_pos->y][cur_pos->x] = '0';
			game_data->map_arr[cur_pos->y + 1][cur_pos->x] = 'P';
		}
	}
	else if (keycode == KEY_D)
	{
		if (game_data->map_arr[cur_pos->y][cur_pos->x + 1] != '1')
		{
			game_data->map_arr[cur_pos->y][cur_pos->x] = '0';
			game_data->map_arr[cur_pos->y][cur_pos->x + 1] = 'P';
		}
	}
	else if (keycode == KEY_ESC)
	{
		mlx_destroy_window(game_data->mlx_ptr, game_data->win_ptr);
		return (0);
	}
	draw_update(*game_data);
}

int main(int argc, char *argv[])
{
	t_game_data game_data;
	t_list *map_list;

	if (argc != 2)
		return (0);
	ft_bzero(&game_data, sizeof(t_game_data));
	map_list = gnl_to_list(argv[1], &game_data.map_width, &game_data.map_height);
	if (!map_list)
		return (0);
	if (!list_to_map_arr(map_list, &game_data))
		return (0);
	game_data.map_width = ft_strlen(game_data.map_arr[0]) - (ft_strchr(game_data.map_arr[0], '\n') > 0);
	if (!map_arr_check(&game_data))
		return (0);
	game_data.mlx_ptr = mlx_init();
	game_data.win_ptr = mlx_new_window(game_data.mlx_ptr, game_data.map_width * 32, game_data.map_height * 32, "so_long");
	
	if (!load_game_res(game_data.mlx_ptr, &game_data.game_res))
		return (0);

	draw_update(game_data);

	mlx_key_hook(game_data.win_ptr, my_key_hook, &game_data);
	mlx_loop(game_data.mlx_ptr);
}