/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesimsek <sesimsek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 16:22:04 by sesimsek          #+#    #+#             */
/*   Updated: 2025/12/29 21:49:45 by sesimsek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

typedef struct s_draw_info
{
	int	line_h;
	int	draw_start;
	int	draw_end;
}	t_draw_info;

static t_img	*get_wall_texture(t_cub *cub, t_rayhit *hit)
{
	if (hit->side == SIDE_X)
	{
		if (hit->map_x > cub->player.pos.x)
			return (&cub->tex.ea);
		else
			return (&cub->tex.we);
	}
	else
	{
		if (hit->map_y > cub->player.pos.y)
			return (&cub->tex.so);
		else
			return (&cub->tex.no);
	}
}

static void	init_side_dist(t_cub *cub, t_rayhit *hit, t_v2 *side_dist)
{
	hit->step_x = -1;
	if (hit->ray_dir.x >= 0)
		hit->step_x = 1;
	hit->step_y = -1;
	if (hit->ray_dir.y >= 0)
		hit->step_y = 1;
	if (hit->ray_dir.x < 0)
		side_dist->x = (cub->player.pos.x - hit->map_x) * hit->delta_dist.x;
	else
		side_dist->x = (hit->map_x + 1.0 - cub->player.pos.x) * hit->delta_dist.x;
	if (hit->ray_dir.y < 0)
		side_dist->y = (cub->player.pos.y - hit->map_y) * hit->delta_dist.y;
	else
		side_dist->y = (hit->map_y + 1.0 - cub->player.pos.y) * hit->delta_dist.y;
}

static void	dda_loop(t_cub *cub, t_rayhit *hit, t_v2 *side_dist)
{
	hit->hit = 0;
	while (!hit->hit)
	{
		if (side_dist->x < side_dist->y)
		{
			side_dist->x += hit->delta_dist.x;
			hit->map_x += hit->step_x;
			hit->side = SIDE_X;
		}
		else
		{
			side_dist->y += hit->delta_dist.y;
			hit->map_y += hit->step_y;
			hit->side = SIDE_Y;
		}
		if (hit->map_x < 0 || hit->map_x >= cub->map.w
			|| hit->map_y < 0 || hit->map_y >= cub->map.h)
			hit->hit = 1;
		else if (cub->map.grid[hit->map_y][hit->map_x] == '1')
			hit->hit = 1;
	}
}

static void	calculate_wall_dist(t_rayhit *hit, t_v2 *side_dist)
{
	if (hit->side == SIDE_X)
		hit->perp_dist = (side_dist->x - hit->delta_dist.x);
	else
		hit->perp_dist = (side_dist->y - hit->delta_dist.y);
	if (hit->perp_dist < 0.0001)
		hit->perp_dist = 0.0001;
}

static void	calculate_wall_x(t_cub *cub, t_rayhit *hit)
{
	if (hit->side == SIDE_X)
		hit->wall_x = cub->player.pos.y + hit->perp_dist * hit->ray_dir.y;
	else
		hit->wall_x = cub->player.pos.x + hit->perp_dist * hit->ray_dir.x;
	hit->wall_x -= floor(hit->wall_x);
}

static void	perform_dda(t_cub *cub, t_rayhit *hit)
{
	t_v2	side_dist;

	init_side_dist(cub, hit, &side_dist);
	dda_loop(cub, hit, &side_dist);
	calculate_wall_dist(hit, &side_dist);
	calculate_wall_x(cub, hit);
}

static void	draw_ceiling(t_cub *cub, int *dst, int draw_start)
{
	int	y;

	y = 0;
	while (y + 3 < draw_start)
	{
		dst[0] = cub->ceil_color_int;
		dst[cub->pixel_stride] = cub->ceil_color_int;
		dst[cub->pixel_stride * 2] = cub->ceil_color_int;
		dst[cub->pixel_stride * 3] = cub->ceil_color_int;
		dst += cub->pixel_stride * 4;
		y += 4;
	}
	while (y < draw_start)
	{
		*dst = cub->ceil_color_int;
		dst += cub->pixel_stride;
		y++;
	}
}


static void	calculate_line_height(t_cub *cub, t_rayhit *hit,
		t_draw_info *info)
{
	double	inv_dist;

	inv_dist = 1.0 / hit->perp_dist;
	info->line_h = (int)(cub->screen_h * inv_dist);
	info->draw_start = -info->line_h / 2 + cub->screen_h / 2;
	if (info->draw_start < 0)
		info->draw_start = 0;
	info->draw_end = info->line_h / 2 + cub->screen_h / 2;
	if (info->draw_end >= cub->screen_h)
		info->draw_end = cub->screen_h - 1;
}

static int	get_tex_x(t_cub *cub, t_rayhit *hit, t_img *tex)
{
	int	tex_x;

	tex_x = (int)(hit->wall_x * (double)tex->w);
	if ((hit->side == SIDE_X && hit->map_x > cub->player.pos.x)
		|| (hit->side == SIDE_Y && hit->map_y < cub->player.pos.y))
		tex_x = tex->w - tex_x - 1;
	return (tex_x);
}

static void	draw_wall(t_cub *cub, int *dst, t_rayhit *hit,
		t_draw_info *info)
{
	t_img	*tex;
	int		tex_x;
	char	*tex_data;
	double	step;
	double	tex_pos;
	int		y;

	tex = get_wall_texture(cub, hit);
	tex_x = get_tex_x(cub, hit, tex);
	tex_data = tex->addr + tex_x * (tex->bpp / 8);
	step = tex->h / (double)info->line_h;
	tex_pos = (info->draw_start - cub->screen_h / 2 + info->line_h / 2) * step;
	y = info->draw_start;
	while (y < info->draw_end)
	{
		*dst = *((int *)(tex_data + ((int)tex_pos & (tex->h - 1))
				* tex->line_len));
		dst += cub->pixel_stride;
		tex_pos += step;
		y++;
	}
}

static void	draw_floor(t_cub *cub, int *dst, int draw_end)
{
	int	y;

	y = draw_end;
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

static void	draw_wall_stripe(t_cub *cub, int x, t_rayhit *hit)
{
	t_draw_info	info;
	int			*dst;

	calculate_line_height(cub, hit, &info);
	dst = (int *)(cub->frame.addr + x * (cub->frame.bpp / 8));
	draw_ceiling(cub, dst, info.draw_start);
	dst += info.draw_start * cub->pixel_stride;
	draw_wall(cub, dst, hit, &info);
	dst = (int *)(cub->frame.addr + x * (cub->frame.bpp / 8))
		+ info.draw_end * cub->pixel_stride;
	draw_floor(cub, dst, info.draw_end);
}

static void	init_ray(t_cub *cub, int x, t_rayhit *hit)
{
	double	camera_x;

	camera_x = x * cub->screen_w_recip - 1.0;
	hit->ray_dir.x = cub->player.dir.x + cub->player.plane.x * camera_x;
	hit->ray_dir.y = cub->player.dir.y + cub->player.plane.y * camera_x;
	if (hit->ray_dir.x == 0)
		hit->delta_dist.x = 1e30;
	else
		hit->delta_dist.x = fabs(1 / hit->ray_dir.x);
	if (hit->ray_dir.y == 0)
		hit->delta_dist.y = 1e30;
	else
		hit->delta_dist.y = fabs(1 / hit->ray_dir.y);
}

void	raycast(t_cub *cub)
{
	int			x;
	t_rayhit	hit;

	x = 0;
	while (x < cub->screen_w)
	{
		init_ray(cub, x, &hit);
		hit.map_x = (int)cub->player.pos.x;
		hit.map_y = (int)cub->player.pos.y;
		perform_dda(cub, &hit);
		draw_wall_stripe(cub, x, &hit);
		x++;
	}
}
