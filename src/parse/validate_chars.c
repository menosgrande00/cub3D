#include "../inc/cub3d.h"

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
	else if (c == 'W')
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

static int	is_allowed_char(char c)
{
	if (c == '0' || c == '1' || c == ' ' || c == 'N'
				|| c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	validate_chars_and_player(t_map *map, t_player *player)
{
	int		x;
	int		y;
	int		seen;
	char	c;

	y = -1;
	seen = 0;
	while (++y < map->h)
	{
		x = -1;
		while(++x < map->w)
		{
			c = map->grid[y][x];
			if (!is_allowed_char(c))
			{
				ft_error("Map include not allowed character");
				return (1);
			}
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (seen != 0)
				{
					ft_error("Player appears more than once");
					return (1);
				}
				seen = 1;
				player->pos.x = (double)x + 0.5;
				player->pos.y = (double)y + 0.5;
				set_player_dir(player, c);
				player->move_speed = 0.08;
				player->rot_speed  = 0.05;
				map->grid[y][x] = '0';
			}
		}
	}
	if (seen == 0)
	{
		ft_error("Player not found");
		return (1);
	}
	return (0);
}
