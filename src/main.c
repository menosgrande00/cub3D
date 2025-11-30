#include "cub3d.h"

static void	init_cub(t_cub *cub)
{
	cub->screen_w = 1920;
	cub->screen_h = 1080;
	cub->cfg.no = NULL;
	cub->cfg.so = NULL;
	cub->cfg.we = NULL;
	cub->cfg.ea = NULL;
	cub->cfg.floor.r = -1;
	cub->cfg.floor.g = -1;
	cub->cfg.floor.b = -1;
	cub->cfg.ceil.r = -1;
	cub->cfg.ceil.g = -1;
	cub->cfg.ceil.b = -1;
}

int main(int argc, char **argv)
{
	t_cub	cub;
	int		fd;

	if (argc == 2)
	{
		init_cub(&cub);
		fd = open(argv[1], O_RDONLY);
		if (set_tex_color_lines(&cub.cfg, fd) || set_map_parse(&cub, fd))
		{
			//free_all(&cub);
			return (1);
		}
		print_cub(&cub);
		create_cub(&cub);

		//printf("%s\n", cub.cfg.no);
		//printf("%s\n", cub.cfg.so);
		//printf("%s\n", cub.cfg.we);
		//printf("%s\n", cub.cfg.ea);

		//int i = -1;
		//while (++i < cub.map.h)
		//	printf("%s\n", cub.map.grid[i]);
	}
	else
		ft_error("Program takes just a 2 arguman!");
	return (0);
}
