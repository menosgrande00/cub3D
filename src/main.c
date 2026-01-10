/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:03:09 by oonal             #+#    #+#             */
/*   Updated: 2026/01/10 16:07:26 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_cub(t_cub *cub)
{
	ft_memset(cub, 0, sizeof(t_cub));
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

static int	check_file_extension(char *filepath)
{
	int		len;
	char	*filename;
	char	*ext;

	filename = ft_strrchr(filepath, '/');
	if (filename)
		filename++;
	else
		filename = filepath;
	len = ft_strlen(filename);
	if (len < 5)
		return (1);
	ext = filename + len - 4;
	if (ft_strcmp(ext, ".cub") != 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub	cub;
	int		fd;

	if (argc == 2)
	{
		if (check_file_extension(argv[1]))
		{
			ft_error("Invalid file extension. Use .cub file");
			return (1);
		}
		init_cub(&cub);
		fd = open(argv[1], O_RDONLY);
		if (set_tex_color_lines(&cub.cfg, fd) || set_map_parse(&cub, fd))
		{
			get_next_line(-1);
			free_cub(&cub);
			return (1);
		}
		create_cub(&cub);
	}
	else
		ft_error("Program takes just a 2 argumans!");
	return (0);
}
