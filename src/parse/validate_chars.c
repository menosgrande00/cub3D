/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_chars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 18:59:39 by sesimsek          #+#    #+#             */
/*   Updated: 2026/01/06 17:27:04 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	set_player_dir2(t_player *p, char c)
{
	if (c == 'W')
	{
		p->dir.x = -1.0;
		p->dir.y = 0.0;
		p->plane.x = 0.0;
		p->plane.y = -0.66;
	}
	else if (c == 'E')
	{
		p->dir.x = 1.0;
		p->dir.y = 0.0;
		p->plane.x = 0.0;
		p->plane.y = 0.66;
	}
}

static void	set_player_dir(t_player *p, char c)
{
	if (c == 'N')
	{
		p->dir.x = 0.0;
		p->dir.y = -1.0;
		p->plane.x = 0.66;
		p->plane.y = 0.0;
	}
	else if (c == 'S')
	{
		p->dir.x = 0.0;
		p->dir.y = 1.0;
		p->plane.x = -0.66;
		p->plane.y = 0.0;
	}
	else if (c == 'W' || c == 'E')
		set_player_dir2(p, c);
}

static void	init_player_params(t_map *map, t_player *player, int x, int y)
{
	player->pos.x = (double)x + 0.5;
	player->pos.y = (double)y + 0.5;
	set_player_dir(player, map->grid[y][x]);
	player->move_speed = 0.03;
	player->rot_speed = 0.02;
	map->grid[y][x] = '0';
}

static int	check_map_char(t_map *map, t_player *player, int x, int y, int *seen)
{
	char	c;

	c = map->grid[y][x];
	if (!is_allowed_char(c))
	{
		ft_error("Map include not allowed character");
		return (1);
	}
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (*seen != 0)
		{
			ft_error("Player appears more than once");
			return (1);
		}
		*seen = 1;
		init_player_params(map, player, x, y);
	}
	return (0);
}

int	validate_chars_and_player(t_map *map, t_player *player)
{
	int	x;
	int	y;
	int	seen;

	y = -1;
	seen = 0;
	while (++y < map->h)
	{
		x = -1;
		while (++x < (int)ft_strlen(map->grid[y]))
		{
			if (check_map_char(map, player, x, y, &seen))
				return (1);
		}
	}
	if (seen == 0)
	{
		ft_error("Player not found");
		return (1);
	}
	return (0);
}
