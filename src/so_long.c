
#include "so_long.h"
#include "../mlx_linux/mlx.h"

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

int is_valid_characters(char *str, char *charset)
{
	while (str)
	{
		if (ft_strchr(charset, *str) == NULL)
			return (0);
	}
	return (1);
}

int gnl_to_list(char *map_file_path, int *map_width, int *map_height)
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
	*map_width = ft_strlen(gnl) - (ft_strchr(gnl, '\n') != 0);
	while (gnl)
	{
		if (!is_valid_characters(gnl, "01CEP"))
			return (0);
		if (*map_width != ft_strlen(gnl) - (ft_strchr(gnl, '\n') != 0))
			return (0);
		new_node = ft_lstnew(gnl);
		if (!new_node)
			return (0);
		ft_lstadd_back(&map_list, new_node);
		*map_height++;
		gnl = get_next_line(fd);
	}
	close(fd);
	return (1);
}
// 옮기기만 하고 체크는 다른함수에서 하는게 나은지...?

int list_to_map_arr(t_game_data game_data)
{
	game_data.map_arr = (char **)malloc(sizeof(char *) * game_data.map_height);
}

int main(int argc, char *argv[])
{
	/*

	gnl로 파일 읽어오기
	문자열에 저장
	strlen으로 문자열 길이 비교로 사각형인지 체크
	exit, collectible, player 의 개수를 세기
	에러 처리

	char **에 이중배열로 저장해서 인덱스로 접근하고싶음...
	창의 크기는...?
	
	*/

	if (argc != 2)
	{
		ft_printf("argv error\n");
		return (0);
	}

	if (ft_strlen(argv[1]) < 4 || ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".ber", 4))
	{
		ft_printf("file type error\n");
		return (0);
	}

	// ------------------- gnl 로 읽어와서 리스트에 저장하는 부분
	int fd;
	fd = open(argv[1], O_RDONLY); // Mac에서는 루트디렉토리 기준으로 경로를 적어줘야 한다 대체 왜.....

	if (fd < 0)
	{
		ft_printf("open error\n");
		return (0); // fd error
	}
	
	size_t map_width = 0;
	size_t map_height = 0;
	t_list *map_lst = NULL;
	char *gnl = get_next_line(fd);
	map_width = ft_strlen(gnl) - (ft_strchr(gnl, '\n') != 0);
	while (gnl)
	{
		ft_printf("%s", gnl);
		if (map_width != ft_strlen(gnl) - (ft_strchr(gnl, '\n') != 0))
		{
			ft_printf("map not rectangle!\n");
			return (0); // map not rectangle, windows에서는 LF를 CRLF로 저장하기 때문에 '\n' 을 인식하는데 지장이 있었음...
		}
		t_list *new;
		new = ft_lstnew(gnl);
		if (!new)
			return (0);
		ft_lstadd_back(&map_lst, new);
		map_height++;
		// free(gnl);
		gnl = get_next_line(fd);
	}
	close(fd);
	if (map_width == 0 || map_height == 0)
		return (0); // map not rectangle
	
	// 벽으로 닫혀있는지
	// 오브젝트들의 갯수가 유효한지: 1개의 플레이어 1개의 출구 최소 1개의 수집물
	// 경로가 유효한지
	// 마음같아선 이중배열을 쓰고싶은데 gnl을 사용하기엔 linked list가 더 좋을까...
	// 단지 map_height를 위해서 매번 읽기만 하고 사용하지 않는것은 낭비같기도 하고...
	//
	// linked list에 담아놓고 map_height 만큼 이중배열을 선언해서
	// 순회하면서 content만 넣어주고 list는 del 없이 clear 하기?

	// -------------- 이중배열로 만들기 위해 리스트를 순회하며 문자열 주소 옮겨주는 부분
	t_list *map_lst_iter = map_lst;
	char **map_arr;
	map_arr = (char **)malloc(sizeof(char *) * map_height);
	for (int i = 0; i < map_height; i++)
	{
		map_arr[i] = map_lst_iter->content;
		map_lst_iter = map_lst_iter->next;
	}

	ft_printf("\n\n");
	for (int j = 0; j < map_height; j++)
	{
		for (int i = 0; i < map_width; i++)
		{
			ft_printf("%c", map_arr[j][i]);
		}
		ft_printf("\n");
	}

	// -------------- 맵 파일의 문자, 벽, 오브젝트갯수 체크 부분
	size_t p_cnt = 0;
	size_t e_cnt = 0;
	size_t c_cnt = 0;
	ft_printf("\n\n");
	for (int j = 0; j < map_height; j++)
	{
		for (int i = 0; i < map_width; i++)
		{
			ft_printf("%c", map_arr[j][i]);
			if ((j == 0 || j == map_height - 1) || (i == 0 || i == map_width - 1))
			{
				if (map_arr[j][i] != '1')
				{
					ft_printf("map (%d, %d) is not closed!\n", i, j);
					return (0);
				}
			}
			//map_arr[j][i];
			if (map_arr[j][i] == 'P')
				p_cnt++;
			else if (map_arr[j][i] == 'E')
				e_cnt++;
			else if (map_arr[j][i] == 'C')
				c_cnt++;
			else if (map_arr[j][i] != '1' && map_arr[j][i] != '0')
			{
				ft_printf("(%d, %d) there wrong char in mapfile!\n", i, j);
				return (0);
			}
		}
		ft_printf("\n");
	}
	if (p_cnt == 0 || p_cnt > 1 || e_cnt == 0 || e_cnt > 1 || c_cnt == 0)
	{
		ft_printf("object count wrong!\n");
		return (0);
	}
	ft_printf("player cnt: %d\n", p_cnt);
	ft_printf("exit cnt: %d\n", e_cnt);
	ft_printf("collectible cnt: %d\n", c_cnt);

	// dfs
	// x, y 를 함께 갖는 구조체가 필요함
	//
	// 해당 구조체로 stack을 만들고
	// stack의 last를 하나씩 뽑아오는것 (prev 연결은...? -> 만들어뒀던 delnode로...?)
	//
	// 해당 좌표로 visit 배열을 체크
	// 방문하지 않았다면 마킹하고 stack에 추가
	// 이동할수없는 구역이거나 이미 방문했다면 그대로 pass
	//
	// 매 루프마다 남아있는 collectible 개수를 체크해서 반복문을 끝낼것인지...?
	// 모든 루프를 끝마치고 마지막에 체크했던 오브젝트 갯수들을 한번에 볼것인지...?
	// collectible을 다 먹어도 exit를 마지막에 만날수있으니 후자가 낫나?

	// ------------- DFS로 유효한 경로가 있는지 체크하는 부분
	char **visit_arr;
	visit_arr = (char **)malloc(sizeof(char *) * map_height);
	for (int i = 0; i < map_height; i++)
		visit_arr[i] = ft_calloc(map_width, sizeof(char));
	t_list *dfs_stack = NULL;
	for (int j = 0; j < map_height; j++)
	{
		for (int i = 0; i < map_width; i++)
		{
			if (map_arr[j][i] == 'P')
			{
				t_vec2d *new_vec2 = (t_vec2d *)malloc(sizeof(t_vec2d));
				new_vec2->x = i;
				new_vec2->y = j;
				t_list *new;
				new = ft_lstnew(new_vec2);
				ft_lstadd_back(&dfs_stack, new);
				visit_arr[j][i] = 1;
				break ;
			}
		}
		if (dfs_stack)
			break ;
	}

	size_t can_exit = 0;
	size_t remain_c = c_cnt;
	while (dfs_stack)
	{
		t_list *cur_node;
		t_vec2d cur_pos;
		cur_node = ft_lstlast(dfs_stack);
		cur_pos.x = ((t_vec2d *)(cur_node->content))->x;
		cur_pos.y = ((t_vec2d *)(cur_node->content))->y;
		ft_lstdel_node(&dfs_stack, cur_node, free);

		if (map_arr[cur_pos.y][cur_pos.x] == 'E')
			can_exit++;
		else if (map_arr[cur_pos.y][cur_pos.x] == 'C')
			remain_c--;

		if (cur_pos.x - 1 >= 0 && visit_arr[cur_pos.y][cur_pos.x - 1] == 0 && map_arr[cur_pos.y][cur_pos.x - 1] != '1')
		{
			t_vec2d *new_vec2 = (t_vec2d *)malloc(sizeof(t_vec2d));
			new_vec2->x = cur_pos.x - 1;
			new_vec2->y = cur_pos.y;
			t_list *new;
			new = ft_lstnew(new_vec2);
			ft_lstadd_back(&dfs_stack, new);
			visit_arr[cur_pos.y][cur_pos.x - 1] = 1;
		}
		if (cur_pos.x + 1 < map_width && visit_arr[cur_pos.y][cur_pos.x + 1] == 0 && map_arr[cur_pos.y][cur_pos.x + 1] != '1')
		{
			t_vec2d *new_vec2 = (t_vec2d *)malloc(sizeof(t_vec2d));
			new_vec2->x = cur_pos.x + 1;
			new_vec2->y = cur_pos.y;
			t_list *new;
			new = ft_lstnew(new_vec2);
			ft_lstadd_back(&dfs_stack, new);
			visit_arr[cur_pos.y][cur_pos.x + 1] = 1;
		}

		if (cur_pos.y - 1 >= 0 && visit_arr[cur_pos.y - 1][cur_pos.x] == 0 && map_arr[cur_pos.y - 1][cur_pos.x] != '1')
		{
			t_vec2d *new_vec2 = (t_vec2d *)malloc(sizeof(t_vec2d));
			new_vec2->x = cur_pos.x;
			new_vec2->y = cur_pos.y - 1;
			t_list *new;
			new = ft_lstnew(new_vec2);
			ft_lstadd_back(&dfs_stack, new);
			visit_arr[cur_pos.y - 1][cur_pos.x] = 1;
		}
		if (cur_pos.y + 1 < map_height && visit_arr[cur_pos.y + 1][cur_pos.x] == 0 && map_arr[cur_pos.y + 1][cur_pos.x] != '1')
		{
			t_vec2d *new_vec2 = (t_vec2d *)malloc(sizeof(t_vec2d));
			new_vec2->x = cur_pos.x;
			new_vec2->y = cur_pos.y + 1;
			t_list *new;
			new = ft_lstnew(new_vec2);
			ft_lstadd_back(&dfs_stack, new);
			visit_arr[cur_pos.y + 1][cur_pos.x] = 1;
		}
	}

	ft_printf("\n");
	if (can_exit == 0 || remain_c > 0)
	{
		ft_printf("invalid path!\n");
		if (remain_c)
			ft_printf("there remain collectible!\n");
		if (!can_exit)
			ft_printf("Can access to exit!\n");
		return (0);
	}

	ft_printf("valid check done\n");
	
	// ------------- mlx 세팅
	t_game_data game_data;

	ft_bzero(game_data, sizeof(t_game_data));
	// 이 타이밍에서 구조체 들고 파싱함수로 들어가야 map_width, map_height, map_arr에 넣어줄수있음
	game_data.mlx_ptr = mlx_init();
	game_data.map_width = map_width;
	game_data.map_height = map_height;
	game_data.map_arr = map_arr;
	game_data.win_ptr = mlx_new_window(game_data.mlx_ptr, game_data.map_width * 32, game_data.map_height * 32, "so_long");
	
	// void *mlx_ptr;
	// void *win_ptr;
	// mlx_ptr = mlx_init();
	// win_ptr = mlx_new_window(mlx_ptr, map_width * 32, map_height * 32, "so_long");

	// ------------- 리소스 불러오는 부분
	if (!load_game_res(game_data.mlx_ptr, &game_data.game_res))
		return (0);
	
	// ------------- 맵 배열 참고하여 화면 그리는 부분
	draw_update(game_data);

	// mlx_key_hook 이랑 연결하기...
	// key_hook부터 연결하고 특정키만 mlx_hook로 덮어쓰면 해당 키는 후자로 후킹될까...?
	// mlx_key_hook 에서 조건부로 배열 업데이트
	// 업데이트 된 배열을 참조해서 다시 그리기

	// mlx_key_hook(win_ptr); // -> 결국 void *param에 넣을 구조체가 필요하다...
	// 공통적으로 쓰일애들 파악하기 ex) mlx_ptr, win_ptr, map_arr(width, height), img_stat(void *img_ptr, char *img_path, int img_width, int img_height), game_resources

	mlx_loop(game_data.mlx_ptr);
}