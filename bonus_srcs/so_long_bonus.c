/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:34:40 by yonghyle          #+#    #+#             */
/*   Updated: 2023/03/18 20:24:44 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	is_rect(char **map_arr, int x, int y)
{
	if (map_arr[y][x] == '1')
		return (0);
	if (map_arr[y - 1][x] != '1')
	{
		if (map_arr[y - 1][x - 1] != '1' && map_arr[y][x - 1] != '1')
			return (1);
		else if (map_arr[y - 1][x + 1] != '1' && map_arr[y][x + 1] != '1')
			return (1);
	}
	else if (map_arr[y + 1][x] != '1')
	{
		if (map_arr[y + 1][x - 1] != '1' && map_arr[y][x - 1] != '1')
			return (1);
		else if (map_arr[y + 1][x + 1] != '1' && map_arr[y][x + 1] != '1')
			return (1);
	}
	return (0);
}

void	create_pat_arr(t_game_data *game_data)
{
	int	y;
	int	x;

	game_data->pat_arr = (char **)malloc(sizeof(char *) * \
	game_data->map_height);
	if (!game_data->pat_arr)
		my_solong_error(game_data, "Failed to create buffer for map file.\n");
	y = 0;
	while (y < game_data->map_height)
	{
		game_data->pat_arr[y] = (char *)malloc(game_data->map_width);
		if (!game_data->pat_arr[y])
			my_solong_error(game_data, "Failed to create buffer for map \
			file.\n");
		x = 0;
		while (x < game_data->map_width)
		{
			game_data->pat_arr[y][x] = is_rect(game_data->map_arr, x, y);
			x++;
		}
		y++;
	}
}

// create enemy
// 가장 큰 사각형을 찾는다
// 최소 사이즈는 2, 2 이다
// 없으면 -1, -1에 박아놓고 움직이지 않는다
// 플레이어 위치와 겹치면 안된다
// 위치를 잘못잡으면 계속해서 재시도한다
//
// 큰 사각형 찾기 알고리즘을 사용하지 말자...
// pat_arr에서 1인 좌표 하나를 변수에 저장하고
// 순회하며 인접한 1당 크기를 잰다
// 순회가 끝나면 다음 좌표를 잡고 잰다
// 가장 사각형이 큰 시작점의 좌표를 반환한다
//
// 그 시작점을 반환받고
// 사각형의 가로, 세로를 다시 구한다
// 그 안에서 랜덤으로 스폰위치를 정한다
// 플레이어와 겹치면 재시도한다
//
// pat_arr에서 1인 좌표가 하나도 없으면
// 반환받은 좌표값을 통해 확인
// 이럴떈 -1, -1에 박아놓고 움직이지 않는다

void	map_arr_check(t_game_data *game_data)
{
	char	**visit_arr;
	t_list	*dfs_stack;

	check_rectangle(*game_data);
	check_valid_characters(*game_data);
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

void	list_to_map_arr(t_list *map_list, t_game_data *game_data)
{
	t_list	*list_iter;
	int		i;

	i = 0;
	list_iter = map_list;
	game_data->map_arr = (char **)malloc(sizeof(char *) * \
	game_data->map_height);
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

t_list	*gnl_to_list(char *map_file_path, t_game_data *game_data)
{
	int		fd;
	t_list	*map_list;
	t_list	*new_node;
	char	*gnl;

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
			my_solong_error(game_data, "Failed to create buffer \
			for map file.\n");
		}
		ft_lstadd_back(&map_list, new_node);
		game_data->map_height++;
		gnl = get_next_line(fd);
	}
	close(fd);
	return (map_list);
}

int	main(int argc, char *argv[])
{
	t_game_data	game_data;
	time_t		t;

	ft_bzero(&game_data, sizeof(t_game_data));
	if (argc != 2)
		my_solong_error(&game_data, "The program was given invalid \
		arguments.\n");
	if (ft_strlen(argv[1]) < 4 || ft_strncmp(argv[1] + ft_strlen(argv[1]) \
	- 4, ".ber", 4))
		my_solong_error(&game_data, "Invalid extension of file.\n");
	list_to_map_arr(gnl_to_list(argv[1], &game_data), &game_data);
	game_data.map_width = ft_strlen(game_data.map_arr[0]) - \
	(ft_strchr(game_data.map_arr[0], '\n') > 0);
	map_arr_check(&game_data);
	create_pat_arr(&game_data);
	srand((unsigned) time(&t));
	game_data.mlx_ptr = mlx_init();
	game_data.win_ptr = mlx_new_window(game_data.mlx_ptr, \
	game_data.map_width * 32, game_data.map_height * 32, "so_long");
	load_game_res(&game_data);
	game_data.enemy_pos.x = 1;
	game_data.enemy_pos.y = 1;
	draw_update(game_data);
	mlx_key_hook(game_data.win_ptr, my_key_hook, &game_data);
	mlx_hook(game_data.win_ptr, 17, 0, my_solong_exit, &game_data);
	mlx_loop(game_data.mlx_ptr);
}
