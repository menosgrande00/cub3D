/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesimsek <sesimsek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 17:13:29 by sesimsek          #+#    #+#             */
/*   Updated: 2026/01/11 19:54:11 by sesimsek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static	double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

static	void	set_texture_pixel(t_cub *cub)
{
	cub->tex.no.img = mlx_xpm_file_to_image(cub->mlx,
			cub->cfg.no, &cub->tex.no.w, &cub->tex.no.h);
	cub->tex.so.img = mlx_xpm_file_to_image(cub->mlx,
			cub->cfg.so, &cub->tex.so.w, &cub->tex.so.h);
	cub->tex.we.img = mlx_xpm_file_to_image(cub->mlx,
			cub->cfg.we, &cub->tex.we.w, &cub->tex.we.h);
	cub->tex.ea.img = mlx_xpm_file_to_image(cub->mlx,
			cub->cfg.ea, &cub->tex.ea.w, &cub->tex.ea.h);
	if (!cub->tex.no.img || !cub->tex.so.img
		|| !cub->tex.we.img || !cub->tex.ea.img)
	{
		ft_error("Error loading texture files (XPM format may be corrupted)");
		free_cub(cub);
	}
	cub->tex.no.addr = mlx_get_data_addr(cub->tex.no.img,
			&cub->tex.no.bpp, &cub->tex.no.line_len, &cub->tex.no.end);
	cub->tex.so.addr = mlx_get_data_addr(cub->tex.so.img,
			&cub->tex.so.bpp, &cub->tex.so.line_len, &cub->tex.so.end);
	cub->tex.we.addr = mlx_get_data_addr(cub->tex.we.img,
			&cub->tex.we.bpp, &cub->tex.we.line_len, &cub->tex.we.end);
	cub->tex.ea.addr = mlx_get_data_addr(cub->tex.ea.img,
			&cub->tex.ea.bpp, &cub->tex.ea.line_len, &cub->tex.ea.end);
}

static	void	set_frame_buffer(t_cub *cub)
{
	cub->frame.img = mlx_new_image(cub->mlx, cub->render_w, cub->render_h);
	cub->frame.addr = mlx_get_data_addr(cub->frame.img,
			&cub->frame.bpp, &cub->frame.line_len, &cub->frame.end);
	cub->frame.w = cub->render_w;
	cub->frame.h = cub->render_h;
	cub->scaled_frame.img = mlx_new_image(cub->mlx, cub->screen_w,
			cub->screen_h);
	cub->scaled_frame.addr = mlx_get_data_addr(cub->scaled_frame.img,
			&cub->scaled_frame.bpp, &cub->scaled_frame.line_len,
			&cub->scaled_frame.end);
	cub->scaled_frame.w = cub->screen_w;
	cub->scaled_frame.h = cub->screen_h;
}

static	void	upscale_frame(t_cub *cub)
{
	int		*src_line;
	int		*dst_line1;
	int		*dst_line2;
	int		sy;
	int		sx;
	int		color;

	sy = -1;
	while (++sy < cub->render_h)
	{
		src_line = (int *)(cub->frame.addr + sy * cub->frame.line_len);
		dst_line1 = (int *)(cub->scaled_frame.addr
				+ (sy * 2) * cub->scaled_frame.line_len);
		dst_line2 = (int *)(cub->scaled_frame.addr
				+ (sy * 2 + 1) * cub->scaled_frame.line_len);
		sx = -1;
		while (++sx < cub->render_w)
		{
			color = src_line[sx];
			dst_line1[sx * 2] = color;
			dst_line1[sx * 2 + 1] = color;
			dst_line2[sx * 2] = color;
			dst_line2[sx * 2 + 1] = color;
		}
	}
}

static	int	render_frame(t_cub *cub)
{
	double	current_time;
	double	instant_fps;

	current_time = get_time();
	cub->delta_time = current_time - cub->last_time;
	if (cub->delta_time > 0.1)
		cub->delta_time = 0.1;
	cub->last_time = current_time;
	if (cub->delta_time > 0.0)
	{
		instant_fps = 1.0 / cub->delta_time;
		if (cub->frame_count == 0)
			cub->fps = instant_fps;
		else
			cub->fps = cub->fps * 0.9 + instant_fps * 0.1;
	}
	cub->frame_count++;
	if (cub->frame_count % 60 == 0)
		printf("FPS: %.1f (avg: %.1f)\n", 1.0 / cub->delta_time, cub->fps);
	handle_input(cub);
	raycast(cub);
	upscale_frame(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->scaled_frame.img, 0, 0);
	return (0);
}

void	create_cub(t_cub *cub)
{
	cub->last_time = get_time();
	cub->fps = 0.0;
	cub->frame_count = 0;
	cub->scale_factor = 2;
	cub->render_w = cub->screen_w / cub->scale_factor;
	cub->render_h = cub->screen_h / cub->scale_factor;
	cub->mlx = mlx_init();
	if (!cub->mlx)
		free_cub(cub);
	set_texture_pixel(cub);
	cub->win = mlx_new_window(cub->mlx, cub->screen_w, cub->screen_h, "cub3D");
	if (!cub->win)
		free_cub(cub);
	set_frame_buffer(cub);
	cub->ceil_color_int = (cub->cfg.ceil.r << 16) | (cub->cfg.ceil.g << 8)
		| cub->cfg.ceil.b;
	cub->floor_color_int = (cub->cfg.floor.r << 16) | (cub->cfg.floor.g << 8)
		| cub->cfg.floor.b;
	cub->pixel_stride = cub->frame.line_len / sizeof(int);
	cub->screen_h_half = cub->render_h / 2;
	cub->screen_w_recip = 2.0 / (double)cub->render_w;
	cub->delta_time = 0.016;
	cub->cos_rot = cos(cub->player.rot_speed * cub->delta_time);
	cub->sin_rot = sin(cub->player.rot_speed * cub->delta_time);
	setup_hooks(cub);
	mlx_loop_hook(cub->mlx, render_frame, cub);
	mlx_loop(cub->mlx);
}
