/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 18:57:02 by sesimsek          #+#    #+#             */
/*   Updated: 2026/01/06 17:17:18 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_after_map(int fd)
{
	char	*line;
	int		i;

	line = get_next_line(fd);
	while (line != NULL)
	{
		i = 0;
		if (line[i] != '\0' && line[i] != '\n')
		{
			free(line);
			ft_error("Map: extra content after map");
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

static	void	norm_to_grid(char **lines, int h, t_map *map)
{
	int		i;
	int		wmax;
	int		len;

	i = -1;
	wmax = 0;
	while (++i < h)
	{
		len = (int)ft_strlen(lines[i]);
		if (len > wmax)
			wmax = len;
	}
	map->grid = malloc(sizeof(char *) * (h + 1));
	map->grid[h] = NULL;
	map->w = wmax;
	map->h = h;
	i = -1;
	while (++i < h)
	{
		len = (int)ft_strlen(lines[i]);
		map->grid[i] = malloc(wmax + 1);
		ft_memset(map->grid[i], ' ', wmax);
		ft_memcpy(map->grid[i], lines[i], len);
		map->grid[i][wmax] = '\0';
	}
}

int	set_map_parse(t_cub *cub, int fd)
{
	char	**lines;
	int		h;

	lines = NULL;
	h = 0;
	if (collect_map_lines(fd, &lines, &h))
		return (1);
	norm_to_grid(lines, h, &cub->map);
	free_double(lines);
	if (validate_chars_and_player(&cub->map, &cub->player)
		|| check_closed_by_walls(&cub->map) || check_after_map(fd))
	{
		return (1);
	}
	return (0);
}
