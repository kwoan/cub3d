/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwpark <kwpark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 21:53:40 by kwpark            #+#    #+#             */
/*   Updated: 2023/03/06 11:21:38 by kwpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main_loop(t_info *info)
{
	raycasting(info);
	draw_buffer(info);
	key_update(info);
	return (0);
}

static void	init_info(t_info *info)
{
	int	i;

	i = 0;
	info->texture = (int **)malloc(sizeof(int *) * 4);
	if (!info->texture)
		exit(1);
	while (i < 4)
	{
		info->texture[i] = malloc(sizeof(int) * (TEXHEIGHT * TEXWIDTH));
		if (!info->texture[i])
		{
			while (--i > 0)
				free(info->texture[i]);
			exit(1);
		}
		i++;
	}
	init_arr(info->texture, 4, TEXHEIGHT * TEXWIDTH, 0);
	init_key(info);
	init_pos(info);
	info->mlx = mlx_init();
	info->win = mlx_new_window(info->mlx, WIDTH, HEIGHT, "cub3D");
	info->img.img = mlx_new_image(info->mlx, WIDTH, HEIGHT);
	info->img.data = (int *)mlx_get_data_addr(info->img.img, &info->img.bpp, \
		&info->img.size_line, &info->img.endian);
}

int	main(int ac, char **av)
{
	t_info		info;

	if (ac != 2 || (check_map_name(av[1]) == 0))
		print_err("ac error\n");
	ft_parse(av[1], &info);
	init_info(&info);
	camera_buf_flush(&info);
	load_texture(&info);
	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, X_EVENT_KEY_RELEASE, 0, &key_release, &info);
	mlx_loop(info.mlx);
}
