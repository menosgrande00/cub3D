/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesimsek <sesimsek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 17:56:55 by sesimsek          #+#    #+#             */
/*   Updated: 2026/01/14 15:30:36 by sesimsek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

#define MOVEMENT_MARGIN 0.2

static int	validate_move_x(t_cub *cub, double new_x)
{
	int	start;
	int	end;
	int	y;
	int	step;

	y = (int)cub->player.pos.y;
	start = (int)cub->player.pos.x;
	if (new_x > cub->player.pos.x)
		end = (int)(new_x + MOVEMENT_MARGIN);
	else
		end = (int)(new_x - MOVEMENT_MARGIN);
	if (start < end)
		step = 1;
	else
		step = -1;
	while (1)
	{
		if (start < 0 || start >= cub->map.w || cub->map.grid[y][start] == '1')
			return (0);
		if (start == end)
			break ;
		start += step;
	}
	return (1);
}

static int	validate_move_y(t_cub *cub, double new_y)
{
	int	start;
	int	end;
	int	x;
	int	step;

	x = (int)cub->player.pos.x;
	start = (int)cub->player.pos.y;
	if (new_y > cub->player.pos.y)
		end = (int)(new_y + MOVEMENT_MARGIN);
	else
		end = (int)(new_y - MOVEMENT_MARGIN);
	if (start < end)
		step = 1;
	else
		step = -1;
	while (1)
	{
		if (start < 0 || start >= cub->map.h || cub->map.grid[start][x] == '1')
			return (0);
		if (start == end)
			break ;
		start += step;
	}
	return (1);
}

static void	apply_movement(t_cub *cub, double new_x, double new_y)
{
	if (validate_move_x(cub, new_x))
		cub->player.pos.x = new_x;
	if (validate_move_y(cub, new_y))
		cub->player.pos.y = new_y;
}

void	move_forward_back(t_cub *cub)
{
	double	new_x;
	double	new_y;
	double	speed;

	speed = cub->player.move_speed * cub->delta_time;
	if (cub->keys.held[119])
	{
		new_x = cub->player.pos.x + cub->player.dir.x * speed;
		new_y = cub->player.pos.y + cub->player.dir.y * speed;
		apply_movement(cub, new_x, new_y);
	}
	if (cub->keys.held[115])
	{
		new_x = cub->player.pos.x - cub->player.dir.x * speed;
		new_y = cub->player.pos.y - cub->player.dir.y * speed;
		apply_movement(cub, new_x, new_y);
	}
}

void	move_strafe(t_cub *cub)
{
	double	new_x;
	double	new_y;
	double	speed;

	speed = cub->player.move_speed * cub->delta_time;
	if (cub->keys.held[100])
	{
		new_x = cub->player.pos.x + cub->player.plane.x * speed;
		new_y = cub->player.pos.y + cub->player.plane.y * speed;
		apply_movement(cub, new_x, new_y);
	}
	if (cub->keys.held[97])
	{
		new_x = cub->player.pos.x - cub->player.plane.x * speed;
		new_y = cub->player.pos.y - cub->player.plane.y * speed;
		apply_movement(cub, new_x, new_y);
	}
}
