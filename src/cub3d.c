/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwpark <kwpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 21:53:40 by kwpark            #+#    #+#             */
/*   Updated: 2023/03/03 02:57:32 by kwpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	worldMap[mapWidth][mapHeight] =
						{
							{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
							{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
							{1,0,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1},
							{1,0,1,0,0,0,0,1,0,1,0,1,0,1,0,1,1,0,0,0,1,1,1,1},
							{1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
							{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
							{1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1},
							{1,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
							{1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
							{1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
							{1,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,0,0,1,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,0,1,1},
							{1,0,1,0,1,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,1},
							{1,0,0,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,0,1,1},
							{1,0,1,0,1,0,0,0,0,1,1,0,1,1,0,0,1,0,0,1,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,0,0,0,1},
							{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
						};

int	main_loop(t_info *info)
{
	raycasting(info);
	draw_buffer(info);
	key_update(info);
	return (0);
}

void	init_info(t_info *info)
{
	int	i;

	i = 0;
	info->texture = (int **)malloc(sizeof(int *) * 4);
	if (!info->texture)
		exit(1);
	while (i < 4)
	{
		if (!(info->texture[i++] = (int *)malloc(sizeof(int) * (texHeight * texWidth))))
		{
			while (--i > 0)
				free(info->texture[i]);
			exit(1);
		}
	}
	init_arr(info->texture, 4, texHeight * texWidth, 0);
	info->moveSpeed = 0.03;
	info->rotSpeed = 0.03;
	info->re_buf = 0;	
	info->key_a = 0;
	info->key_w = 0;
	info->key_s = 0;
	info->key_d = 0;
	info->key_esc = 0;
	
	info->posX = 22.0;
	info->posY = 11.5;
	info->dirX = -1.0;
	info->dirY = 0.0;
	info->planeX = 0.0;
	info->planeY = 0.66;

	info->mlx = mlx_init();
	info->win = mlx_new_window(info->mlx, width, height, "CUB3D");
	info->img.img = mlx_new_image(info->mlx, width, height);
	info->img.data = (int *)mlx_get_data_addr(info->img.img, &info->img.bpp, &info->img.size_line, &info->img.endian);
}

void	init_mapinfo(t_info *info, t_mapinfo *mapinfo)
{
	info->mapinfo = mapinfo;
	
	info->mapinfo->color_c = 0xff0000;
	info->mapinfo->color_f = 0x0000ff;
	info->mapinfo->path_no = "textures/NO.xpm";
	info->mapinfo->path_so = "textures/SO.xpm";
	info->mapinfo->path_we = "textures/WE.xpm";
	info->mapinfo->path_ea = "textures/EA.xpm";

	/*
		init_pos --> as function(ex. get_dirX)
	*/

	camera_buf_flush(info);
}

int	main(int ac, char **av)
{
	t_info		info;
	t_mapinfo	mapinfo;

	(void)ac;
	(void)av;

	/*
			map_parse(ac, av, mapinfo);
	*/
	
	init_mapinfo(&info, &mapinfo);
	init_info(&info);
	load_texture(&info);
	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, X_EVENT_KEY_RELEASE, 0, &key_release, &info);	
	mlx_loop(info.mlx);
}