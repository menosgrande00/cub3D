/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesimsek <sesimsek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 17:55:27 by sesimsek          #+#    #+#             */
/*   Updated: 2025/12/24 21:07:16 by sesimsek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// Kamera rotasyonu (sağ/sol ok tuşları)
// Sağ ok tuşu - Sağa dön // Right arrow
// Sol ok tuşu - Sola dön // Left arrow
static	void	rotate_camera_right(t_cub *cub, double old_dir_x,
	double old_plane_x, double rot_speed)
{
	old_dir_x = cub->player.dir.x;
	cub->player.dir.x = cub->player.dir.x * cos(rot_speed)
		- cub->player.dir.y * sin(rot_speed);
	cub->player.dir.y = old_dir_x * sin(rot_speed)
		+ cub->player.dir.y * cos(rot_speed);
	old_plane_x = cub->player.plane.x;
	cub->player.plane.x = cub->player.plane.x * cos(rot_speed)
		- cub->player.plane.y * sin(rot_speed);
	cub->player.plane.y = old_plane_x * sin(rot_speed)
		+ cub->player.plane.y * cos(rot_speed);
}

static	void	rotate_camera_left(t_cub *cub, double old_dir_x,
		double old_plane_x, double rot_speed)
{
	old_dir_x = cub->player.dir.x;
	cub->player.dir.x = cub->player.dir.x * cos(-rot_speed)
		- cub->player.dir.y * sin(-rot_speed);
	cub->player.dir.y = old_dir_x * sin(-rot_speed)
		+ cub->player.dir.y * cos(-rot_speed);
	old_plane_x = cub->player.plane.x;
	cub->player.plane.x = cub->player.plane.x * cos(-rot_speed)
		- cub->player.plane.y * sin(-rot_speed);
	cub->player.plane.y = old_plane_x * sin(-rot_speed)
		+ cub->player.plane.y * cos(-rot_speed);
}

void	rotate_camera(t_cub *cub)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	old_dir_x = 0;
	old_plane_x = 0;
	rot_speed = cub->player.rot_speed;
	if (cub->keys.held[65363])
	{
		rotate_camera_right(cub, old_dir_x, old_plane_x, rot_speed);
	}
	if (cub->keys.held[65361])
	{
		rotate_camera_left(cub, old_dir_x, old_plane_x, rot_speed);
	}
}
