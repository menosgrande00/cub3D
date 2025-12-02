#include "../cub3d.h"

int	close_window(t_cub *cub)
{
	(void)cub;
	exit(0);
	return (0);
}

int	key_press(int keycode, t_cub *cub)
{
	if (keycode == 65307)
		close_window(cub);
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