/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_dda.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesimsek <sesimsek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 00:00:00 by sesimsek          #+#    #+#             */
/*   Updated: 2026/01/26 21:50:30 by sesimsek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_side_dist(t_cub *cub, t_v2 *side_dist)
{
	cub->hit.step_x = 1;
	if (cub->hit.ray_dir.x < 0)
	{
		cub->hit.step_x = -1;
		side_dist->x = (cub->player.pos.x - cub->hit.map_x)
			* cub->hit.delta_dist.x;
	}
	else
		side_dist->x = (cub->hit.map_x + 1.0 - cub->player.pos.x)
			* cub->hit.delta_dist.x;
	cub->hit.step_y = 1;
	if (cub->hit.ray_dir.y < 0)
	{
		cub->hit.step_y = -1;
		side_dist->y = (cub->player.pos.y - cub->hit.map_y)
			* cub->hit.delta_dist.y;
	}
	else
		side_dist->y = (cub->hit.map_y + 1.0 - cub->player.pos.y)
			* cub->hit.delta_dist.y;
}

static void	dda_loop(t_cub *cub, t_v2 *side_dist)
{
	cub->hit.hit = 0;
	while (!cub->hit.hit)
	{
		if (side_dist->x < side_dist->y)
		{
			side_dist->x += cub->hit.delta_dist.x;
			cub->hit.map_x += cub->hit.step_x;
			cub->hit.side = SIDE_X;
		}
		else
		{
			side_dist->y += cub->hit.delta_dist.y;
			cub->hit.map_y += cub->hit.step_y;
			cub->hit.side = SIDE_Y;
		}
		if (cub->hit.map_x < 0 || cub->hit.map_x >= cub->map.w
			|| cub->hit.map_y < 0 || cub->hit.map_y >= cub->map.h)
			cub->hit.hit = 1;
		else if (cub->map.grid[cub->hit.map_y][cub->hit.map_x] == '1')
			cub->hit.hit = 1;
	}
}

static void	calculate_wall_dist(t_cub *cub, t_v2 *side_dist)
{
	if (cub->hit.side == SIDE_X)
		cub->hit.perp_dist = (side_dist->x - cub->hit.delta_dist.x);
	else
		cub->hit.perp_dist = (side_dist->y - cub->hit.delta_dist.y);
	if (cub->hit.perp_dist < 0.0001)
		cub->hit.perp_dist = 0.0001;
}

static void	calculate_wall_x(t_cub *cub)
{
	if (cub->hit.side == SIDE_X)
		cub->hit.wall_x = cub->player.pos.y + cub->hit.perp_dist
			* cub->hit.ray_dir.y;
	else
		cub->hit.wall_x = cub->player.pos.x + cub->hit.perp_dist
			* cub->hit.ray_dir.x;
	cub->hit.wall_x -= floor(cub->hit.wall_x);
}

void	perform_dda(t_cub *cub)
{
	t_v2	side_dist;

	init_side_dist(cub, &side_dist);
	dda_loop(cub, &side_dist);
	calculate_wall_dist(cub, &side_dist);
	calculate_wall_x(cub);
}
