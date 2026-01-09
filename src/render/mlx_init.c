/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesimsek <sesimsek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 17:13:29 by sesimsek          #+#    #+#             */
/*   Updated: 2026/01/09 19:49:51 by sesimsek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	cub->frame.img = mlx_new_image(cub->mlx, cub->screen_w, cub->screen_h);
	cub->frame.addr = mlx_get_data_addr(cub->frame.img,
			&cub->frame.bpp, &cub->frame.line_len, &cub->frame.end);
	cub->frame.w = cub->screen_w;
	cub->frame.h = cub->screen_h;
}

static	int	render_frame(t_cub *cub)
{
	handle_input(cub);
	raycast(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->frame.img, 0, 0);
	return (0);
}

void	create_cub(t_cub *cub)
{
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
	cub->screen_w_recip = 2.0 / (double)cub->screen_w;
	cub->cos_rot = cos(cub->player.rot_speed);
	cub->sin_rot = sin(cub->player.rot_speed);
	setup_hooks(cub);
	mlx_loop_hook(cub->mlx, render_frame, cub);
	mlx_loop(cub->mlx);
}
