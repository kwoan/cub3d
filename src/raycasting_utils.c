/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwpark <kwpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:42:08 by kwpark            #+#    #+#             */
/*   Updated: 2023/03/03 02:55:54 by kwpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	get_texnum(t_raycast *rc)
{
	if (rc->side == 0)
	{
		if (rc->rayDirX > 0)
			return ((int)WE);
		else
			return ((int)EA);
	}
	else
	{
		if (rc->rayDirY > 0)
			return ((int)NO);
		else
			return ((int)SO);
	}
}

void	camera_buf_flush(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (i < (int)height / 2)
				info->buf[i][j] = info->mapinfo->color_c;
			else
				info->buf[i][j] = info->mapinfo->color_f;
			j++;
		}
		i++;
	}
}

void	draw_texture(t_info *info, t_raycast *rc, t_tex *tex, int x)
{
	int	y;

	y = rc->drawStart;
	while (y < rc->drawEnd)
	{
		tex->texY = (int)tex->texPos & (texHeight - 1);
		tex->texPos += tex->step;
		tex->color = \
			info->texture[tex->texNum][texHeight * tex->texY + tex->texX];
		if (rc->side == 1)
			tex->color = (tex->color >> 1) & 8355711;
		info->buf[y][x] = tex->color;
		info->re_buf = 1;
		y++;
	}
}
