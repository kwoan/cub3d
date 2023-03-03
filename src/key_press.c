/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwpark <kwpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 23:22:02 by kwpark            #+#    #+#             */
/*   Updated: 2023/03/03 02:59:23 by kwpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	move_dir(t_info *info, double dir)
{
	double	move_dir;

	move_dir = dir * info->moveSpeed;
	if (!worldMap[(int)(info->posX + info->dirX * move_dir)][(int)info->posY])
		info->posX += info->dirX * move_dir;
	if (!worldMap[(int)info->posX][(int)(info->posY + info->dirY * move_dir)])
		info->posY += info->dirY * move_dir;
}

static void	rot_dir(t_info *info, double dir)
{
	double	olddirx;
	double	oldplanex;
	double	rot_dir;

	rot_dir = info->rotSpeed * dir;
	olddirx = info->dirX;
	info->dirX = info->dirX * cos(rot_dir) - info->dirY * sin(rot_dir);
	info->dirY = olddirx * sin(rot_dir) + info->dirY * cos(rot_dir);
	oldplanex = info->planeX;
	info->planeX = info->planeX * cos(rot_dir) - info->planeY * sin(rot_dir);
	info->planeY = oldplanex * sin(rot_dir) + info->planeY * cos(rot_dir);
}

void	key_update(t_info *info)
{
	if (info->key_w)
		move_dir(info, 1.0);
	if (info->key_s)
		move_dir(info, -1.0);
	if (info->key_a)
		rot_dir(info, 1.0);
	if (info->key_d)
		rot_dir(info, -1.0);
	if (info->key_esc)
		exit(0);
}

int	key_press(int key, t_info *info)
{
	if (key == K_ESC)
		exit(0);
	else if (key == K_W)
		info->key_w = 1;
	else if (key == K_A)
		info->key_a = 1;
	else if (key == K_S)
		info->key_s = 1;
	else if (key == K_D)
		info->key_d = 1;
	return (0);
}

int	key_release(int key, t_info *info)
{
	if (key == K_ESC)
		exit(0);
	else if (key == K_W)
		info->key_w = 0;
	else if (key == K_A)
		info->key_a = 0;
	else if (key == K_S)
		info->key_s = 0;
	else if (key == K_D)
		info->key_d = 0;
	return (0);
}
