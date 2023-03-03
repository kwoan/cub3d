/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwpark <kwpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 02:13:15 by kwpark            #+#    #+#             */
/*   Updated: 2023/03/03 02:58:36 by kwpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	load_image(t_info *info, int *texture, char *path, t_img *img)
{
	int	x;
	int	y;

	img->img = mlx_xpm_file_to_image(info->mlx, path, \
							&img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, \
									&img->size_line, &img->endian);
	y = 0;
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_width)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(info->mlx, img->img);
}

void	load_texture(t_info *info)
{
	t_img	img;

	load_image(info, info->texture[0], info->mapinfo->path_no, &img);
	load_image(info, info->texture[1], info->mapinfo->path_we, &img);
	load_image(info, info->texture[2], info->mapinfo->path_so, &img);
	load_image(info, info->texture[3], info->mapinfo->path_ea, &img);
}

void	init_arr(int **arr, int size1, int size2, int value)
{
	int	i;
	int	j;

	i = 0;
	while (i < size1)
	{
		j = 0;
		while (j < size2)
		{
			arr[i][j] = value;
			j++;
		}
		i++;
	}
}

void	draw_buffer(t_info *info)
{
	int	x;
	int	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			info->img.data[y * width + x] = info->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}
