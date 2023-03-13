
#include "so_long.h"
// #include "../mlx_linux/mlx.h"

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
				t_vec2 *new_vec2 = (t_vec2 *)malloc(sizeof(t_vec2));
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
		t_vec2 cur_pos;
		cur_node = ft_lstlast(dfs_stack);
		cur_pos.x = ((t_vec2 *)(cur_node->content))->x;
		cur_pos.y = ((t_vec2 *)(cur_node->content))->y;
		ft_lstdel_node(&dfs_stack, cur_node, free);

		if (map_arr[cur_pos.y][cur_pos.x] == 'E')
			can_exit++;
		else if (map_arr[cur_pos.y][cur_pos.x] == 'C')
			remain_c--;

		if (cur_pos.x - 1 >= 0 && visit_arr[cur_pos.y][cur_pos.x - 1] == 0 && map_arr[cur_pos.y][cur_pos.x - 1] != '1')
		{
			t_vec2 *new_vec2 = (t_vec2 *)malloc(sizeof(t_vec2));
			new_vec2->x = cur_pos.x - 1;
			new_vec2->y = cur_pos.y;
			t_list *new;
			new = ft_lstnew(new_vec2);
			ft_lstadd_back(&dfs_stack, new);
			visit_arr[cur_pos.y][cur_pos.x - 1] = 1;
		}
		if (cur_pos.x + 1 < map_width && visit_arr[cur_pos.y][cur_pos.x + 1] == 0 && map_arr[cur_pos.y][cur_pos.x + 1] != '1')
		{
			t_vec2 *new_vec2 = (t_vec2 *)malloc(sizeof(t_vec2));
			new_vec2->x = cur_pos.x + 1;
			new_vec2->y = cur_pos.y;
			t_list *new;
			new = ft_lstnew(new_vec2);
			ft_lstadd_back(&dfs_stack, new);
			visit_arr[cur_pos.y][cur_pos.x + 1] = 1;
		}

		if (cur_pos.y - 1 >= 0 && visit_arr[cur_pos.y - 1][cur_pos.x] == 0 && map_arr[cur_pos.y - 1][cur_pos.x] != '1')
		{
			t_vec2 *new_vec2 = (t_vec2 *)malloc(sizeof(t_vec2));
			new_vec2->x = cur_pos.x;
			new_vec2->y = cur_pos.y - 1;
			t_list *new;
			new = ft_lstnew(new_vec2);
			ft_lstadd_back(&dfs_stack, new);
			visit_arr[cur_pos.y - 1][cur_pos.x] = 1;
		}
		if (cur_pos.y + 1 < map_height && visit_arr[cur_pos.y + 1][cur_pos.x] == 0 && map_arr[cur_pos.y + 1][cur_pos.x] != '1')
		{
			t_vec2 *new_vec2 = (t_vec2 *)malloc(sizeof(t_vec2));
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
	void *mlx_ptr;
	void *win_ptr;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, map_width * 32, map_height * 32, "my so_long project");
	int img_width = 0;
	int img_height = 0;
	void *spr_empty = mlx_xpm_file_to_image(mlx_ptr, "./res/sprite/empty_space.xpm", &img_width, &img_height); // 여기서 상대위치는 소스파일이 아니라 실행파일 기준으로 한다...어째서??
	void *spr_wall = mlx_xpm_file_to_image(mlx_ptr, "./res/sprite/wall.xpm", &img_width, &img_height);
	void *spr_collectible = mlx_xpm_file_to_image(mlx_ptr, "./res/sprite/collectible.xpm", &img_width, &img_height);
	void *spr_exit = mlx_xpm_file_to_image(mlx_ptr, "./res/sprite/exit.xpm", &img_width, &img_height);
	void *spr_player1 = mlx_xpm_file_to_image(mlx_ptr, "./res/sprite/player1.xpm", &img_width, &img_height);
	
	// ------------- 맵 배열 참고하여 화면 그리는 부분
	for (int j = 0; j < map_height; j++)
	{
		for (int i = 0; i < map_width; i++)
		{
			if (map_arr[j][i] == '0')
				mlx_put_image_to_window(mlx_ptr, win_ptr, spr_empty, i * img_width, j * img_height);
			else if (map_arr[j][i] == '1')
				mlx_put_image_to_window(mlx_ptr, win_ptr, spr_wall, i * img_width, j * img_height);
			else if (map_arr[j][i] == 'C')
				mlx_put_image_to_window(mlx_ptr, win_ptr, spr_collectible, i * img_width, j * img_height);
			else if (map_arr[j][i] == 'E')
				mlx_put_image_to_window(mlx_ptr, win_ptr, spr_exit, i * img_width, j * img_height);
			else if (map_arr[j][i] == 'P')
				mlx_put_image_to_window(mlx_ptr, win_ptr, spr_player1, i * img_width, j * img_height);
		}
	}

	// mlx_key_hook 이랑 연결하기...
	// key_hook부터 연결하고 특정키만 mlx_hook로 덮어쓰면 해당 키는 후자로 후킹될까...?
	// mlx_key_hook 에서 조건부로 배열 업데이트
	// 업데이트 된 배열을 참조해서 다시 그리기

	// mlx_key_hook(win_ptr); // -> 결국 void *param에 넣을 구조체가 필요하다... 공통적으로 쓰일애들 파악하기 ex) map_arr

	mlx_loop(mlx_ptr);
}