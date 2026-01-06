/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesimsek <sesimsek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 16:22:04 by sesimsek          #+#    #+#             */
/*   Updated: 2026/01/06 20:55:10 by sesimsek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	calculate_line_height(t_cub *cub)
{
	double	inv_dist;

	inv_dist = 1.0 / cub->hit.perp_dist;
	cub->draw.line_h = (int)(cub->screen_h * inv_dist);
	cub->draw.draw_start = -cub->draw.line_h / 2 + cub->screen_h / 2;
	if (cub->draw.draw_start < 0)
		cub->draw.draw_start = 0;
	cub->draw.draw_end = cub->draw.line_h / 2 + cub->screen_h / 2;
	if (cub->draw.draw_end >= cub->screen_h)
		cub->draw.draw_end = cub->screen_h - 1;
}

static	void	draw_floor(t_cub *cub, int *dst)
{
	int	y;

	y = cub->draw.draw_end;
	while (y + 3 < cub->screen_h)
	{
		dst[0] = cub->floor_color_int;
		dst[cub->pixel_stride] = cub->floor_color_int;
		dst[cub->pixel_stride * 2] = cub->floor_color_int;
		dst[cub->pixel_stride * 3] = cub->floor_color_int;
		dst += cub->pixel_stride * 4;
		y += 4;
	}
	while (y < cub->screen_h)
	{
		*dst = cub->floor_color_int;
		dst += cub->pixel_stride;
		y++;
	}
}

static void	draw_wall_stripe(t_cub *cub, int x)
{
	int	*dst;

	calculate_line_height(cub);
	dst = (int *)(cub->frame.addr + x * (cub->frame.bpp / 8));
	draw_ceiling(cub, dst);
	dst += cub->draw.draw_start * cub->pixel_stride;
	draw_wall(cub, dst);
	dst = (int *)(cub->frame.addr + x * (cub->frame.bpp / 8))
		+ cub->draw.draw_end * cub->pixel_stride;
	draw_floor(cub, dst);
}

static void	init_ray(t_cub *cub, int x)
{
	double	camera_x;

	camera_x = x * cub->screen_w_recip - 1.0;
	cub->hit.ray_dir.x = cub->player.dir.x + cub->player.plane.x * camera_x;
	cub->hit.ray_dir.y = cub->player.dir.y + cub->player.plane.y * camera_x;
	if (cub->hit.ray_dir.x == 0)
		cub->hit.delta_dist.x = 1e30;
	else
		cub->hit.delta_dist.x = fabs(1 / cub->hit.ray_dir.x);
	if (cub->hit.ray_dir.y == 0)
		cub->hit.delta_dist.y = 1e30;
	else
		cub->hit.delta_dist.y = fabs(1 / cub->hit.ray_dir.y);
}

void	raycast(t_cub *cub)
{
	int	x;

	x = 0;
	while (x < cub->screen_w)
	{
		init_ray(cub, x);
		cub->hit.map_x = (int)cub->player.pos.x;
		cub->hit.map_y = (int)cub->player.pos.y;
		perform_dda(cub);
		draw_wall_stripe(cub, x);
		x++;
	}
}
