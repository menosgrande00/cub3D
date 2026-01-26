/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesimsek <sesimsek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 17:55:27 by sesimsek          #+#    #+#             */
/*   Updated: 2026/01/13 16:01:02 by sesimsek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static	void	rotate_camera_right(t_cub *cub, double old_dir_x,
	double old_plane_x)
{
	old_dir_x = cub->player.dir.x;
	cub->player.dir.x = cub->player.dir.x * cub->cos_rot
		- cub->player.dir.y * cub->sin_rot;
	cub->player.dir.y = old_dir_x * cub->sin_rot
		+ cub->player.dir.y * cub->cos_rot;
	old_plane_x = cub->player.plane.x;
	cub->player.plane.x = cub->player.plane.x * cub->cos_rot
		- cub->player.plane.y * cub->sin_rot;
	cub->player.plane.y = old_plane_x * cub->sin_rot
		+ cub->player.plane.y * cub->cos_rot;
}

static	void	rotate_camera_left(t_cub *cub, double old_dir_x,
		double old_plane_x)
{
	old_dir_x = cub->player.dir.x;
	cub->player.dir.x = cub->player.dir.x * cub->cos_rot
		+ cub->player.dir.y * cub->sin_rot;
	cub->player.dir.y = -old_dir_x * cub->sin_rot
		+ cub->player.dir.y * cub->cos_rot;
	old_plane_x = cub->player.plane.x;
	cub->player.plane.x = cub->player.plane.x * cub->cos_rot
		+ cub->player.plane.y * cub->sin_rot;
	cub->player.plane.y = -old_plane_x * cub->sin_rot
		+ cub->player.plane.y * cub->cos_rot;
}

void	rotate_camera(t_cub *cub)
{
	cub->cos_rot = cos(cub->player.rot_speed * cub->delta_time);
	cub->sin_rot = sin(cub->player.rot_speed * cub->delta_time);
	if (cub->keys.held[65363])
		rotate_camera_right(cub, 0, 0);
	if (cub->keys.held[65361])
		rotate_camera_left(cub, 0, 0);
}
