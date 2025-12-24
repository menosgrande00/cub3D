/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesimsek <sesimsek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 16:22:04 by sesimsek          #+#    #+#             */
/*   Updated: 2025/12/24 16:27:33 by sesimsek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

// Bir dikey çizgi (duvar dilimi) çiz - Cache-optimized
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
	int		ceil_color;
	int		floor_color;
	int		*dst;
	int		x_offset;
	int		pixel_stride;
	char	*tex_data;
	int		tex_line_len;

	// Duvar yüksekliğini hesapla (reciprocal multiplication - faster)
	double inv_dist = 1.0 / hit->perp_dist;
	line_h = (int)(cub->screen_h * inv_dist);
	draw_start = -line_h / 2 + cub->screen_h / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_h / 2 + cub->screen_h / 2;
	if (draw_end >= cub->screen_h)
		draw_end = cub->screen_h - 1;

	// Renkleri önceden hesapla (döngü dışında)
	ceil_color = (cub->cfg.ceil.r << 16) | (cub->cfg.ceil.g << 8) | cub->cfg.ceil.b;
	floor_color = (cub->cfg.floor.r << 16) | (cub->cfg.floor.g << 8) | cub->cfg.floor.b;

	// Pointer arithmetic için hazırlık (cache-friendly sequential access)
	x_offset = x * (cub->frame.bpp / 8);
	pixel_stride = cub->frame.line_len / sizeof(int);
	dst = (int *)(cub->frame.addr + x_offset);

	// Tavan çiz (0'dan draw_start'a kadar) - Sequential write (SIMD-friendly)
	y = 0;
	// Loop unrolling hint için 4'lü gruplar (CPU cache line = 64 bytes = 16 pixels)
	while (y + 3 < draw_start)
	{
		dst[0] = ceil_color;
		dst[pixel_stride] = ceil_color;
		dst[pixel_stride * 2] = ceil_color;
		dst[pixel_stride * 3] = ceil_color;
		dst += pixel_stride * 4;
		y += 4;
	}
	// Kalan pixelleri işle
	while (y < draw_start)
	{
		*dst = ceil_color;
		dst += pixel_stride;
		y++;
	}

	// Texture koordinatlarını hesapla
	tex = get_wall_texture(cub, hit);
	tex_x = (int)(hit->wall_x * (double)tex->w);
	if ((hit->side == SIDE_X && hit->map_x > cub->player.pos.x) ||
		(hit->side == SIDE_Y && hit->map_y < cub->player.pos.y))
		tex_x = tex->w - tex_x - 1;

	// Texture pointer ve stride (cache locality için)
	tex_data = tex->addr + tex_x * (tex->bpp / 8);
	tex_line_len = tex->line_len / sizeof(int);

	// Texture mapping için step ve başlangıç pozisyonu (optimized)
	double inv_line_h = 1.0 / line_h;
	step = tex->h * inv_line_h;
	tex_pos = (draw_start - cub->screen_h / 2 + line_h / 2) * step;

	// Duvar çiz - Optimized texture lookup
	y = draw_start;
	while (y < draw_end)
	{
		tex_y = (int)tex_pos & (tex->h - 1);
		tex_pos += step;
		// Direct texture memory access (cache-friendly)
		*dst = *((int *)(tex_data + tex_y * tex->line_len));
		dst += pixel_stride;
		y++;
	}

	// Zemin çiz (draw_end'den screen_h'ye kadar) - Sequential write (SIMD-friendly)
	// Loop unrolling - 4 pixel birden
	while (y + 3 < cub->screen_h)
	{
		dst[0] = floor_color;
		dst[pixel_stride] = floor_color;
		dst[pixel_stride * 2] = floor_color;
		dst[pixel_stride * 3] = floor_color;
		dst += pixel_stride * 4;
		y += 4;
	}
	// Kalan pixelleri işle
	while (y < cub->screen_h)
	{
		*dst = floor_color;
		dst += pixel_stride;
		y++;
	}
}

// Ana raycast fonksiyonu - Cache & CPU optimized
void	raycast(t_cub *cub)
{
	int			x;
	double		camera_x;
	t_v2		ray_dir;
	t_v2		delta_dist;
	t_rayhit	hit;
	double		screen_w_recip;

	// Division'ı loop dışına taşı (CPU cache + branch predictor friendly)
	screen_w_recip = 2.0 / (double)cub->screen_w;
	x = 0;
	while (x < cub->screen_w)
	{
		// Kamera X koordinatı (-1 ile 1 arası) - multiplication only
		camera_x = x * screen_w_recip - 1.0;
		
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
