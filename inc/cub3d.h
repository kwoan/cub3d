/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwpark <kwpark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:10:20 by kwpark            #+#    #+#             */
/*   Updated: 2023/02/28 00:03:14 by kwpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include "key_macos.h"

#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_EXIT	17
#define mapWidth 24
#define mapHeight 24
#define width 640
#define height 480

extern int  worldMap[24][24];

typedef struct  s_raycast
{
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	deltaDistX;
	double	deltaDistY;
	double	sideDistX;
	double	sideDistY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;

	int		color;
}               t_raycast;

typedef struct	s_info
{
	double  posX;
	double  posY;
	double  dirX;
	double  dirY;
	double  planeX;
	double  planeY;
	void    *mlx;
	void    *win;
	double  moveSpeed;
	double  rotSpeed;
}               t_info;

void	draw_line(t_info *info, int x, int y1, int y2, int color);
void    raycasting(t_info *info);
int	    key_press(int key, t_info *info);


#endif