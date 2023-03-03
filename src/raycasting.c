/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwpark <kwpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 23:21:28 by kwpark            #+#    #+#             */
/*   Updated: 2023/03/03 02:56:12 by kwpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	set_dda_vars(t_info *info, t_raycast *rc)
{
	rc->mapX = (int)(info->posX);
	rc->mapY = (int)(info->posY);
	rc->deltaDistX = fabs(1 / rc->rayDirX);
	rc->deltaDistY = fabs(1 / rc->rayDirY);
	rc->hit = 0;
	if (rc->rayDirX < 0)
	{
		rc->stepX = -1;
		rc->sideDistX = (info->posX - rc->mapX) * rc->deltaDistX;
	}
	else
	{
		rc->stepX = 1;
		rc->sideDistX = (rc->mapX + 1.0 - info->posX) * rc->deltaDistX;
	}
	if (rc->rayDirY < 0)
	{
		rc->stepY = -1;
		rc->sideDistY = (info->posY - rc->mapY) * rc->deltaDistY;
	}
	else
	{
		rc->stepY = 1;
		rc->sideDistY = (rc->mapY + 1.0 - info->posY) * rc->deltaDistY;
	}
}

static void	dda_algorithm(t_raycast *rc)
{
	while (rc->hit == 0)
	{
		if (rc->sideDistX < rc->sideDistY)
		{
			rc->sideDistX += rc->deltaDistX;
			rc->mapX += rc->stepX;
			rc->side = 0;
		}
		else
		{
			rc->sideDistY += rc->deltaDistY;
			rc->mapY += rc->stepY;
			rc->side = 1;
		}
		if (worldMap[rc->mapX][rc->mapY] > 0)
			rc->hit = 1;
	}
}

static void	set_texture(t_info *info, t_raycast *rc, int x)
{
	t_tex	tex;

	rc->drawStart = -rc->lineHeight / 2 + height / 2;
	if (rc->drawStart < 0)
		rc->drawStart = 0;
	rc->drawEnd = rc->lineHeight / 2 + height / 2;
	if (rc->drawEnd >= height)
		rc->drawEnd = height - 1;
	tex.texNum = get_texnum(rc);
	if (rc->side == 0)
		tex.wallX = info->posY + rc->perpWallDist * rc->rayDirY;
	else
		tex.wallX = info->posX + rc->perpWallDist * rc->rayDirX;
	tex.wallX -= floor(tex.wallX);
	tex.texX = (int)(tex.wallX * (double)texWidth);
	if (rc->side == 0 && rc->rayDirX > 0)
		tex.texX = texWidth - tex.texX - 1;
	if (rc->side == 1 && rc->rayDirY < 0)
		tex.texX = texWidth - tex.texX - 1;
	tex.step = 1.0 * texHeight / rc->lineHeight;
	tex.texPos = (rc->drawStart - height / 2 + rc->lineHeight / 2) * tex.step;
	draw_texture(info, rc, &tex, x);
}

static void	get_perp(t_info *info, t_raycast *rc)
{
	if (rc->side == 0)
		rc->perpWallDist = \
			(rc->mapX - info->posX + (1 - rc->stepX) / 2) / rc->rayDirX;
	else
		rc->perpWallDist = \
			(rc->mapY - info->posY + (1 - rc->stepY) / 2) / rc->rayDirY;
	rc->lineHeight = (int)(height / rc->perpWallDist);
}

void	raycasting(t_info *info)
{
	int			x;
	t_raycast	rc;

	x = 0;
	if (info->re_buf == 1)
		camera_buf_flush(info);
	while (x < width)
	{
		rc.cameraX = 2 * x / (double)width - 1;
		rc.rayDirX = info->dirX + info->planeX * rc.cameraX;
		rc.rayDirY = info->dirY + info->planeY * rc.cameraX;
		set_dda_vars(info, &rc);
		dda_algorithm(&rc);
		get_perp(info, &rc);
		set_texture(info, &rc, x);
		x++;
	}
}
