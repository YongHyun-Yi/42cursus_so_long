/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_dfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:39:08 by yonghyle          #+#    #+#             */
/*   Updated: 2023/03/17 13:40:33 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
