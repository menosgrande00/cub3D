/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesimsek <sesimsek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 16:22:04 by sesimsek          #+#    #+#             */
/*   Updated: 2025/12/21 16:34:18 by sesimsek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	get_texture_color(t_img *tex, int tex_x, int tex_y)
{
	char	*pixel;
	int		offset;

	if (tex_x < 0 || tex_x >= tex->w || tex_y < 0 || tex_y >= tex->h)
		return (0);
	offset = (tex_y * tex->line_len) + (tex_x * (tex->bpp / 8));
	pixel = tex->addr + offset;
	return (*(int *)pixel);
}

// Hangi texture kullanılacağını belirle
static t_img	*get_wall_texture(t_cub *cub, t_rayhit *hit)
{
	if (hit->side == SIDE_X)
	{
		if (hit->map_x > cub->player.pos.x)
			return (&cub->tex.ea);  // Doğu
		else
			return (&cub->tex.we);  // Batı
	}
	else
	{
		if (hit->map_y > cub->player.pos.y)
			return (&cub->tex.so);  // Güney
		else
			return (&cub->tex.no);  // Kuzey
	}
}

// DDA algoritması ile ray casting yap
static void	perform_dda(t_cub *cub, t_rayhit *hit, t_v2 *ray_dir, t_v2 *delta_dist)
{
	t_v2	side_dist;
	int		step_x;
	int		step_y;

	// Başlangıç adımlarını ve mesafelerini hesapla
	step_x = (ray_dir->x < 0) ? -1 : 1;
	step_y = (ray_dir->y < 0) ? -1 : 1;
	side_dist.x = (ray_dir->x < 0) ? 
		(cub->player.pos.x - hit->map_x) * delta_dist->x :
		(hit->map_x + 1.0 - cub->player.pos.x) * delta_dist->x;
	side_dist.y = (ray_dir->y < 0) ?
		(cub->player.pos.y - hit->map_y) * delta_dist->y :
		(hit->map_y + 1.0 - cub->player.pos.y) * delta_dist->y;

	// DDA: duvara çarpana kadar grid'de ilerle
	hit->hit = 0;
	while (!hit->hit)
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta_dist->x;
			hit->map_x += step_x;
			hit->side = SIDE_X;
		}
		else
		{
			side_dist.y += delta_dist->y;
			hit->map_y += step_y;
			hit->side = SIDE_Y;
		}
		// Harita sınırlarını kontrol et ve duvar kontrolü yap
		if (hit->map_x < 0 || hit->map_x >= cub->map.w ||
			hit->map_y < 0 || hit->map_y >= cub->map.h)
			hit->hit = 1;
		else if (cub->map.grid[hit->map_y][hit->map_x] == '1')
			hit->hit = 1;
	}

	// Duvara dik mesafeyi hesapla (fish-eye effect'i önlemek için)
	if (hit->side == SIDE_X)
		hit->perp_dist = (hit->map_x - cub->player.pos.x + 
			(1 - step_x) / 2) / ray_dir->x;
	else
		hit->perp_dist = (hit->map_y - cub->player.pos.y + 
			(1 - step_y) / 2) / ray_dir->y;

	// Duvarda texture koordinatı hesapla
	if (hit->side == SIDE_X)
		hit->wall_x = cub->player.pos.y + hit->perp_dist * ray_dir->y;
	else
		hit->wall_x = cub->player.pos.x + hit->perp_dist * ray_dir->x;
	hit->wall_x -= floor(hit->wall_x);
}

// Bir dikey çizgi (duvar dilimi) çiz
static void	draw_wall_stripe(t_cub *cub, int x, t_rayhit *hit)
{
	t_img	*tex;
	int		line_h;
	int		draw_start;
	int		draw_end;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		y;
	int		color;
	int		ceil_color;
	int		floor_color;
	char	*pixel;

	// Duvar yüksekliğini hesapla
	line_h = (int)(cub->screen_h / hit->perp_dist);
	draw_start = -line_h / 2 + cub->screen_h / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_h / 2 + cub->screen_h / 2;
	if (draw_end >= cub->screen_h)
		draw_end = cub->screen_h - 1;

	// Renkleri önceden hesapla
	ceil_color = (cub->cfg.ceil.r << 16) | (cub->cfg.ceil.g << 8) | cub->cfg.ceil.b;
	floor_color = (cub->cfg.floor.r << 16) | (cub->cfg.floor.g << 8) | cub->cfg.floor.b;

	// Tavan çiz (0'dan draw_start'a kadar)
	y = 0;
	while (y < draw_start)
	{
		pixel = cub->frame.addr + (y * cub->frame.line_len + x * (cub->frame.bpp / 8));
		*(int *)pixel = ceil_color;
		y++;
	}

	// Texture koordinatlarını hesapla
	tex = get_wall_texture(cub, hit);
	tex_x = (int)(hit->wall_x * (double)tex->w);
	if ((hit->side == SIDE_X && hit->map_x > cub->player.pos.x) ||
		(hit->side == SIDE_Y && hit->map_y < cub->player.pos.y))
		tex_x = tex->w - tex_x - 1;

	// Texture mapping için step ve başlangıç pozisyonu
	step = 1.0 * tex->h / line_h;
	tex_pos = (draw_start - cub->screen_h / 2 + line_h / 2) * step;

	// Duvar çiz
	y = draw_start;
	while (y < draw_end)
	{
		tex_y = (int)tex_pos & (tex->h - 1);
		tex_pos += step;
		color = get_texture_color(tex, tex_x, tex_y);
		pixel = cub->frame.addr + (y * cub->frame.line_len + x * (cub->frame.bpp / 8));
		*(int *)pixel = color;
		y++;
	}

	// Zemin çiz (draw_end'den screen_h'ye kadar)
	while (y < cub->screen_h)
	{
		pixel = cub->frame.addr + (y * cub->frame.line_len + x * (cub->frame.bpp / 8));
		*(int *)pixel = floor_color;
		y++;
	}
}

// Ana raycast fonksiyonu
void	raycast(t_cub *cub)
{
	int			x;
	double		camera_x;
	t_v2		ray_dir;
	t_v2		delta_dist;
	t_rayhit	hit;

	x = 0;
	while (x < cub->screen_w)
	{
		// Kamera X koordinatı (-1 ile 1 arası)
		camera_x = 2 * x / (double)cub->screen_w - 1;
		
		// Ray yönünü hesapla
		ray_dir.x = cub->player.dir.x + cub->player.plane.x * camera_x;
		ray_dir.y = cub->player.dir.y + cub->player.plane.y * camera_x;

		// Delta mesafe (bir grid square ilerlemek için gereken ray uzunluğu)
		delta_dist.x = (ray_dir.x == 0) ? 1e30 : fabs(1 / ray_dir.x);
		delta_dist.y = (ray_dir.y == 0) ? 1e30 : fabs(1 / ray_dir.y);

		// Başlangıç map pozisyonu
		hit.map_x = (int)cub->player.pos.x;
		hit.map_y = (int)cub->player.pos.y;

		// DDA ile duvara çarp
		perform_dda(cub, &hit, &ray_dir, &delta_dist);

		// Duvar çizgisini çiz
		draw_wall_stripe(cub, x, &hit);
		x++;
	}
}
