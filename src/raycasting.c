/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwpark <kwpark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 23:21:28 by kwpark            #+#    #+#             */
/*   Updated: 2023/02/28 16:39:18 by kwpark           ###   ########.fr       */
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
	rc->drawStart = -rc->lineHeight / 2 + height / 2;
	if (rc->drawStart < 0)
		rc->drawStart = 0;
	rc->drawEnd = rc->lineHeight / 2 + height / 2;
	if (rc->drawEnd >= height)
		rc->drawEnd = height - 1;
	// if (worldMap[rc->mapY][rc->mapX] == 1)
	// 	rc->color = 0xFF0000;
	// else if (worldMap[rc->mapY][rc->mapX] == 2)
	// 	rc->color = 0x00FF00;
	// else if (worldMap[rc->mapY][rc->mapX] == 3)
	// 	rc->color = 0x0000FF;
	// else if (worldMap[rc->mapY][rc->mapX] == 4)
	// 	rc->color = 0xFFFFFF;
	// else
	// 	rc->color = 0xFFFF00;
	// if (rc->side == 1)
	// 	rc->color = rc->color / 2;

	/*
		textture mapping test
	*/
	// texturing calculations
	int texNum = worldMap[rc->mapX][rc->mapY];

	// calculate value of wallX
	double wallX;
	if (rc->side == 0)
		wallX = info->posY + rc->perpWallDist * rc->rayDirY;
	else
		wallX = info->posX + rc->perpWallDist * rc->rayDirX;
	wallX -= floor(wallX);

	// x coordinate on the texture
	int texX = (int)(wallX * (double)texWidth);
	if (rc->side == 0 && rc->rayDirX > 0)
		texX = texWidth - texX - 1;
	if (rc->side == 1 && rc->rayDirY < 0)
		texX = texWidth - texX - 1;

	// How much to increase the texture coordinate perscreen pixel
	double step = 1.0 * texHeight / rc->lineHeight;
	// Starting texture coordinate
	double texPos = (rc->drawStart - height / 2 + rc->lineHeight / 2) * step;
	for (int y = rc->drawStart; y < rc->drawEnd; y++)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		int texY = (int)texPos & (texHeight - 1);
		texPos += step;
		int color = info->texture[texNum][texHeight * texY + texX];
		// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		if (rc->side == 1)
			color = (color >> 1) & 8355711;
		info->buf[y][x] = color;
		info->re_buf = 1;
	}
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
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				info->buf[i][j] = 0;
			}
		}
	}
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
