/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwpark <kwpark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:39:42 by jaeywon           #+#    #+#             */
/*   Updated: 2023/03/06 09:55:49 by kwpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_map(t_map *map)
{
	map->count = 0;
	map->check = 1;
	map->f_color = -1;
	map->c_color = -1;
	map->start = 0;
	map->w = 0;
	map->h = 0;
	map->map = NULL;
	map->dir_ea = NULL;
	map->dir_no = NULL;
	map->dir_so = NULL;
	map->dir_we = NULL;
}

void	init_player(t_player *player)
{
	player->status = -1;
	player->x = 0;
	player->y = 0;
}

void	init_pos(t_info *info)
{
	info->pos_x = info->player.x;
	info->pos_y = info->player.y;
	if (info->player.status == N)
	{
		info->dir_x = 0.0;
		info->dir_y = -1.0;
		info->plane_x = -0.66;
		info->plane_y = 0.0;
	}
	else if (info->player.status == S)
	{
		info->dir_x = 0.0;
		info->dir_y = 1.0;
		info->plane_x = 0.66;
		info->plane_y = 0.0;
	}
	else if (info->player.status == E)
	{
		info->dir_x = 1.0;
		info->dir_y = 0.0;
		info->plane_x = 0.0;
		info->plane_y = -0.66;
	}
	else if (info->player.status == W)
	{
		info->dir_x = -1.0;
		info->dir_y = 0.0;
		info->plane_x = 0.0;
		info->plane_y = 0.66;
	}
}

void	init_key(t_info *info)
{
	info->move_speed = 0.03;
	info->rot_speed = 0.03;
	info->re_buf = 0;
	info->key_a = 0;
	info->key_w = 0;
	info->key_s = 0;
	info->key_d = 0;
	info->key_ar_l = 0;
	info->key_ar_r = 0;
	info->key_esc = 0;
}
