/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwpark <kwpark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 23:21:28 by kwpark            #+#    #+#             */
/*   Updated: 2023/02/27 23:53:06 by kwpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	draw_line(t_info *info, int x, int y1, int y2, int color)
{
	int	y;

	y = y1;
	while (y <= y2)
	{
		mlx_pixel_put(info->mlx, info->win, x, y, color);
		y++;
	}
}

static void set_dda_vars(t_info *info, t_raycast *rc, int x)
{
    rc->cameraX = 2 * x / (double)width - 1;
    rc->rayDirX = info->dirX + info->planeX * rc->cameraX;
    rc->rayDirY = info->dirY + info->planeY * rc->cameraX;

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

static void dda_algorithm(t_raycast *rc)
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

static void set_texture(t_raycast *rc)
{
    rc->drawStart = -rc->lineHeight / 2 + height / 2;
    if (rc->drawStart < 0)
        rc->drawStart = 0;
    rc->drawEnd = rc->lineHeight / 2 + height / 2;
    if (rc->drawEnd >= height)
        rc->drawEnd = height - 1;
    if (worldMap[rc->mapY][rc->mapX] == 1)
        rc->color = 0xFF0000;
    else if (worldMap[rc->mapY][rc->mapX] == 2)
        rc->color = 0x00FF00;
    else if (worldMap[rc->mapY][rc->mapX] == 3)
        rc->color = 0x0000FF;
    else if (worldMap[rc->mapY][rc->mapX] == 4)
        rc->color = 0xFFFFFF;
    else
        rc->color = 0xFFFF00;
    if (rc->side == 1)
        rc->color = rc->color / 2;
}

static void get_perpWallDist(t_info *info, t_raycast *rc)
{
    if (rc->side == 0)
        rc->perpWallDist = (rc->mapX - info->posX + (1 - rc->stepX) / 2) / rc->rayDirX;
    else
        rc->perpWallDist = (rc->mapY - info->posY + (1 - rc->stepY) / 2) / rc->rayDirY;
    rc->lineHeight = (int)(height / rc->perpWallDist);
}

void    raycasting(t_info *info)
{
	int		    x;
    t_raycast   rc;
    
	x = 0;
	while (x < width)
	{
        set_dda_vars(info, &rc, x);
        dda_algorithm(&rc);
        get_perpWallDist(info, &rc);
        set_texture(&rc);
		draw_line(info, x, rc.drawStart, rc.drawEnd, rc.color);
		x++;
	}
}
