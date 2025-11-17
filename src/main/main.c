#include "../inc/cub3d.h"

int main(int argc, char **argv)
{
	t_cub	cub;
	int		fd;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (set_tex_color_lines(&cub.cfg, fd) || set_map_parse(&cub, fd))
		{
			free_all(&cub);
			return (1);
		}
	}
	else
		ft_error("Program takes just a 2 arguman!");
	return (0);
}
