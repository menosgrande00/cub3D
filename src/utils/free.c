/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesimsek <sesimsek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:38:59 by sesimsek          #+#    #+#             */
/*   Updated: 2026/01/06 20:38:35 by sesimsek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static	void	free_cfg(t_cub *cub)
{
	if (cub->cfg.no)
		free(cub->cfg.no);
	if (cub->cfg.so)
		free(cub->cfg.so);
	if (cub->cfg.we)
		free(cub->cfg.we);
	if (cub->cfg.ea)
		free(cub->cfg.ea);
}

void	free_cub(t_cub *cub)
{
	if (!cub)
		return ;
	if (cub->mlx)
	{
		if (cub->tex.no.img)
			mlx_destroy_image(cub->mlx, cub->tex.no.img);
		if (cub->tex.so.img)
			mlx_destroy_image(cub->mlx, cub->tex.so.img);
		if (cub->tex.we.img)
			mlx_destroy_image(cub->mlx, cub->tex.we.img);
		if (cub->tex.ea.img)
			mlx_destroy_image(cub->mlx, cub->tex.ea.img);
		if (cub->frame.img)
			mlx_destroy_image(cub->mlx, cub->frame.img);
		if (cub->win)
			mlx_destroy_window(cub->mlx, cub->win);
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
	free_cfg(cub);
	if (cub->cfg.map_lines)
		free_double(cub->cfg.map_lines);
	if (cub->map.grid)
		free_double(cub->map.grid);
	exit(1);
}
