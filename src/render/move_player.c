/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesimsek <sesimsek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 17:56:55 by sesimsek          #+#    #+#             */
/*   Updated: 2025/12/20 18:02:56 by sesimsek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// Yeni pozisyonun geçerli olup olmadığını kontrol et
// ilk if Harita sınırları içinde mi?
// ikinci if Duvar var mı?
static	int	is_valid_pos(t_cub *cub, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= cub->map.w
		|| map_y < 0 || map_y >= cub->map.h)
		return (0);
	if (cub->map.grid[map_y][map_x] == '1')
		return (0);
	return (1);
}

// İleri/geri hareket (W/S)
void	move_forward_back(t_cub *cub)
{
	double	new_x;
	double	new_y;

	if (cub->keys.held[119])
	{
		new_x = cub->player.pos.x + cub->player.dir.x * cub->player.move_speed;
		new_y = cub->player.pos.y + cub->player.dir.y * cub->player.move_speed;
		if (is_valid_pos(cub, new_x, cub->player.pos.y))
			cub->player.pos.x = new_x;
		if (is_valid_pos(cub, cub->player.pos.x, new_y))
			cub->player.pos.y = new_y;
	}
	if (cub->keys.held[115])
	{
		new_x = cub->player.pos.x - cub->player.dir.x * cub->player.move_speed;
		new_y = cub->player.pos.y - cub->player.dir.y * cub->player.move_speed;
		if (is_valid_pos(cub, new_x, cub->player.pos.y))
			cub->player.pos.x = new_x;
		if (is_valid_pos(cub, cub->player.pos.x, new_y))
			cub->player.pos.y = new_y;
	}
}

// Sağa/sola hareket (D/A)
void	move_strafe(t_cub *cub)
{
	double	new_x;
	double	new_y;

	if (cub->keys.held[100])
	{
		new_x = cub->player.pos.x + cub->player.plane.x
			* cub->player.move_speed;
		new_y = cub->player.pos.y + cub->player.plane.y
			* cub->player.move_speed;
		if (is_valid_pos(cub, new_x, cub->player.pos.y))
			cub->player.pos.x = new_x;
		if (is_valid_pos(cub, cub->player.pos.x, new_y))
			cub->player.pos.y = new_y;
	}
	if (cub->keys.held[97])
	{
		new_x = cub->player.pos.x - cub->player.plane.x
			* cub->player.move_speed;
		new_y = cub->player.pos.y - cub->player.plane.y
			* cub->player.move_speed;
		if (is_valid_pos(cub, new_x, cub->player.pos.y))
			cub->player.pos.x = new_x;
		if (is_valid_pos(cub, cub->player.pos.x, new_y))
			cub->player.pos.y = new_y;
	}
}
