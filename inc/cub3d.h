/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwpark <kwpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:10:20 by kwpark            #+#    #+#             */
/*   Updated: 2023/03/03 02:54:53 by kwpark           ###   ########.fr       */
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
# define X_EVENT_KEY_RELEASE	3
#define X_EVENT_KEY_EXIT	17
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24
#define width 640
#define height 480

#define NO	0
#define WE	1
#define SO	2
#define EA	3

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
}               t_raycast;

typedef struct	s_tex
{
	int		texNum;
	double	wallX;
	int		texX;
	int		texY;
	double	step;
	double	texPos;
	int		color;
}				t_tex;

typedef struct	s_img
{
	void	*img;
	int		*data;
	int		size_line;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct	s_mapinfo
{
	char	*path_no;
	char	*path_so;
	char	*path_we;
	char	*path_ea;

	int		color_c;
	int		color_f;

	/*
		int	worldMap[mapHeight][mapWidth];

		int	mapWidth;
		int	mapHeight;
	*/
}				t_mapinfo;

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

	t_img	img;
	int		buf[height][width];
	int		**texture;
	int		re_buf;

	int		key_a;
	int		key_w;
	int		key_s;
	int		key_d;
	int		key_esc;

	t_mapinfo *mapinfo;
}               t_info;

void    raycasting(t_info *info);
void	key_update(t_info *info);
int		key_press(int key, t_info *info);
int		key_release(int key, t_info *info);

int		get_texnum(t_raycast *rc);
void	camera_buf_flush(t_info *info);
void	draw_texture(t_info *info, t_raycast *rc, t_tex *tex, int x);

void	init_arr(int **arr, int size1, int size2, int value);
void	load_texture(t_info *info);
void	draw_buffer(t_info *info);


#endif