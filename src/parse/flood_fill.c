#include "../inc/cub3d.h"

static char	**two_expanded_grid(t_map *map)
{
	int		y;
	int		x;
	char	**g;

	y = -1;
	map->f.w_2 = map->w + 2;
	map->f.h_2 = map->h + 2;
	g = malloc(sizeof(char *) * (map->f.h_2 + 1));
	while (++y < map->f.h_2)
	{
		g[y] = malloc((map->f.w_2) + 1);
		x = -1;
		while (++x < map->f.w_2)
			g[y][x] = ' ';
		g[y][map->f.w_2] = '\0';
	}
	g[map->f.h_2] = NULL;
	y = -1;
	while (++y < map->h)
	{
		x = -1;
		while (++x < map->w)
			g[y + 1][x + 1] = map->grid[y][x];
	}
	return (g);
}

static char	**alloc_v(t_map *map)
{
	char	**vis;
	int		y;
	int		x;

	vis = malloc(sizeof(char *) * (map->f.h_2 + 1));
	y = -1;
	while (++y < map->f.h_2)
	{
		vis[y] = malloc(map->f.w_2);
		x = -1;
		while (++x < map->f.w_2)
			vis[y][x] = 0;
	}
	vis[map->f.h_2] = NULL;
	return (vis);
}

static int	bfs_check(t_f *f, char **g, char **v, int i)
{
	f->cx = f->qx[f->head];
	f->cy = f->qy[f->head];
	while (++i < 4)
	{
		f->nx = f->cx + f->dx[i];
		f->ny = f->cy + f->dy[i];
		if (f->nx < 0 || f->ny < 0 || f->nx >= f->w_2 || f->ny >= f->h_2)
			continue ;
		if (v[f->ny][f->nx])
			continue ;
		if (g[f->ny][f->nx] == '0')
		{
			ft_error("Map is not closed by walls");
			return (1);
		}
		if (g[f->ny][f->nx] == ' ')
		{
			v[f->ny][f->nx] = 1;
			f->qx[f->tail] = f->nx;
			f->qy[f->tail] = f->ny;
			f->tail++;
		}
	}
	return (0);
}

static int	bfs(t_map *map, char **g, char **v)
{
	t_f *f;
	int	i;

	f = &map->f;
	f->qx = malloc(sizeof(int) * (f->w_2 * f->h_2));
	f->qy = malloc(sizeof(int) * (f->w_2 * f->h_2));
	f->tail = 1;
	f->head = -1;
	f->qx[0] = 0;
	f->qy[0] = 0;
	v[0][0] = 1;
	while (++f->head < f->tail)
	{
		i = -1;
		if (bfs_check(f, g, v, i))
		{
			free(f->qx);
			free(f->qy);
			return (1);
		}
	}
	free(f->qx);
	free(f->qy);
	return (0);
}

int	check_closed_by_walls(t_map *map)
{
	char	**g;
	char	**v;

	map->f.dx[0] = 1;
	map->f.dx[1] = -1;
	map->f.dx[2] = 0;
	map->f.dx[3] = 0;
	map->f.dy[0] = 0;
	map->f.dy[1] = 0;
	map->f.dy[2] = 1;
	map->f.dy[3] = -1;
	g = two_expanded_grid(map);
	v = alloc_v(map);
	if (bfs(map, g, v))
	{
		free_double(g);
		free_double(v);
		return (1);
	}
	free_double(g);
	free_double(v);
	return (0);
}
