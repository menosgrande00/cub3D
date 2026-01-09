/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesimsek <sesimsek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 18:02:10 by sesimsek          #+#    #+#             */
/*   Updated: 2026/01/09 19:55:15 by sesimsek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	close_window(t_cub *cub)
{
	free_cub(cub);
	return (0);
}

static	void	speed(t_cub *cub, double move_speed, double rot_speed)
{
	cub->player.move_speed = move_speed;
	cub->player.rot_speed = rot_speed;
	cub->cos_rot = cos(cub->player.rot_speed);
	cub->sin_rot = sin(cub->player.rot_speed);
}

int	key_press(int keycode, t_cub *cub)
{
	if (keycode == 65307)
		close_window(cub);
	if (keycode == 49)
		speed(cub, 0.03, 0.02);
	else if (keycode == 50)
		speed(cub, 0.05, 0.03);
	else if (keycode == 51)
		speed(cub, 0.08, 0.05);
	else if (keycode == 52)
		speed(cub, 0.12, 0.08);
	if (keycode < KEY_MAX)
		cub->keys.held[keycode] = 1;
	return (0);
}

int	key_release(int keycode, t_cub *cub)
{
	if (keycode < KEY_MAX)
		cub->keys.held[keycode] = 0;
	return (0);
}

void	setup_hooks(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < KEY_MAX)
		cub->keys.held[i] = 0;
	mlx_hook(cub->win, 17, 0, close_window, cub);
	mlx_hook(cub->win, 2, 1L << 0, key_press, cub);
	mlx_hook(cub->win, 3, 1L << 1, key_release, cub);
}
