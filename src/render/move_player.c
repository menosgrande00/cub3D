/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesimsek <sesimsek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 17:56:55 by sesimsek          #+#    #+#             */
/*   Updated: 2025/12/30 20:03:12 by sesimsek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	apply_movement(t_cub *cub, double new_x, double new_y)
{
	if ((int)new_x >= 0 && (int)new_x < cub->map.w
		&& cub->map.grid[(int)cub->player.pos.y][(int)new_x] != '1')
		cub->player.pos.x = new_x;
	if ((int)new_y >= 0 && (int)new_y < cub->map.h
		&& cub->map.grid[(int)new_y][(int)cub->player.pos.x] != '1')
		cub->player.pos.y = new_y;
}

void	move_forward_back(t_cub *cub)
{
	double	new_x;
	double	new_y;

	if (cub->keys.held[119])
	{
		new_x = cub->player.pos.x + cub->player.dir.x * cub->player.move_speed;
		new_y = cub->player.pos.y + cub->player.dir.y * cub->player.move_speed;
		apply_movement(cub, new_x, new_y);
	}
	if (cub->keys.held[115])
	{
		new_x = cub->player.pos.x - cub->player.dir.x * cub->player.move_speed;
		new_y = cub->player.pos.y - cub->player.dir.y * cub->player.move_speed;
		apply_movement(cub, new_x, new_y);
	}
}

void	move_strafe(t_cub *cub)
{
	double	new_x;
	double	new_y;

	if (cub->keys.held[100])
	{
		new_x = cub->player.pos.x + cub->player.plane.x
			* cub->player.move_speed;
		new_y = cub->player.pos.y + cub->player.plane.y
			* cub->player.move_speed;
		apply_movement(cub, new_x, new_y);
	}
	if (cub->keys.held[97])
	{
		new_x = cub->player.pos.x - cub->player.plane.x
			* cub->player.move_speed;
		new_y = cub->player.pos.y - cub->player.plane.y
			* cub->player.move_speed;
		apply_movement(cub, new_x, new_y);
	}
}
