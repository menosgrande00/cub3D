/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesimsek <sesimsek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 00:00:00 by sesimsek          #+#    #+#             */
/*   Updated: 2026/01/11 19:32:43 by sesimsek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_img	*get_wall_texture(t_cub *cub)
{
	if (cub->hit.side == SIDE_X)
	{
		if (cub->hit.map_x > cub->player.pos.x)
			return (&cub->tex.ea);
		else
			return (&cub->tex.we);
	}
	else
	{
		if (cub->hit.map_y > cub->player.pos.y)
			return (&cub->tex.so);
		else
			return (&cub->tex.no);
	}
}

static int	get_tex_x(t_cub *cub, t_img *tex)
{
	int	tex_x;

	tex_x = (int)(cub->hit.wall_x * (double)tex->w);
	if ((cub->hit.side == SIDE_X && cub->hit.map_x > cub->player.pos.x)
		|| (cub->hit.side == SIDE_Y && cub->hit.map_y < cub->player.pos.y))
		tex_x = tex->w - tex_x - 1;
	return (tex_x);
}

void	draw_ceiling(t_cub *cub, int *dst)
{
	int	y;

	y = 0;
	while (y + 3 < cub->draw.draw_start)
	{
		dst[0] = cub->ceil_color_int;
		dst[cub->pixel_stride] = cub->ceil_color_int;
		dst[cub->pixel_stride * 2] = cub->ceil_color_int;
		dst[cub->pixel_stride * 3] = cub->ceil_color_int;
		dst += cub->pixel_stride * 4;
		y += 4;
	}
	while (y < cub->draw.draw_start)
	{
		*dst = cub->ceil_color_int;
		dst += cub->pixel_stride;
		y++;
	}
}

static void	draw_wall_column(t_cub *cub, int *dst, char *tex_data, t_img *tex)
{
	double	step;
	double	tex_pos;
	int		y;

	step = tex->h / (double)cub->draw.line_h;
	tex_pos = (cub->draw.draw_start - cub->screen_h_half
			+ (cub->draw.line_h >> 1)) * step;
	y = cub->draw.draw_start;
	while (y < cub->draw.draw_end)
	{
		*dst = *((int *)(tex_data + ((int)tex_pos & (tex->h - 1))
					* tex->line_len));
		dst += cub->pixel_stride;
		tex_pos += step;
		y++;
	}
}

void	draw_wall(t_cub *cub, int *dst)
{
	t_img	*tex;
	int		tex_x;
	char	*tex_data;

	tex = get_wall_texture(cub);
	tex_x = get_tex_x(cub, tex);
	tex_data = tex->addr + tex_x * (tex->bpp / 8);
	draw_wall_column(cub, dst, tex_data, tex);
}
