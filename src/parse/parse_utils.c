/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:01:02 by oonal             #+#    #+#             */
/*   Updated: 2026/01/10 16:01:05 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_writed_two_times(char **split, t_cfg *cfg)
{
	if (!ft_strcmp(split[0], "NO") && cfg->no)
		return (1);
	else if (!ft_strcmp(split[0], "SO") && cfg->so)
		return (1);
	else if (!ft_strcmp(split[0], "WE") && cfg->we)
		return (1);
	else if (!ft_strcmp(split[0], "EA") && cfg->ea)
		return (1);
	return (0);
}

int	assign_tex(char **split, t_cfg *cfg)
{
	if (is_writed_two_times(split, cfg))
	{
		ft_error("Texture or color written more than once");
		return (1);
	}
	if (!ft_strcmp(split[0], "NO"))
		cfg->no = ft_strdup(split[1]);
	else if (!ft_strcmp(split[0], "SO"))
		cfg->so = ft_strdup(split[1]);
	else if (!ft_strcmp(split[0], "WE"))
		cfg->we = ft_strdup(split[1]);
	else if (!ft_strcmp(split[0], "EA"))
		cfg->ea = ft_strdup(split[1]);
	return (0);
}

void	set_color(t_cfg *cfg, char *first, char **colors, int i)
{
	if (first[0] == 'F' && i == 0)
		cfg->floor.r = ft_atoi(colors[0]);
	else if (first[0] == 'F' && i == 1)
		cfg->floor.g = ft_atoi(colors[1]);
	else if (first[0] == 'F' && i == 2)
		cfg->floor.b = ft_atoi(colors[2]);
	else if (first[0] == 'C' && i == 0)
		cfg->ceil.r = ft_atoi(colors[0]);
	else if (first[0] == 'C' && i == 1)
		cfg->ceil.g = ft_atoi(colors[1]);
	else if (first[0] == 'C' && i == 2)
		cfg->ceil.b = ft_atoi(colors[2]);
}

int	check_tex_color_value(t_cfg *cfg)
{
	if (!in_range(cfg->floor.r) || !in_range(cfg->floor.g)
		|| !in_range(cfg->floor.b) || !in_range(cfg->ceil.r)
		|| !in_range(cfg->ceil.g) || !in_range(cfg->ceil.b))
	{
		ft_error("RGB colors have to between 0 to 255!");
		return (1);
	}
	if (!cfg->no || !cfg->so || !cfg->we || !cfg->ea)
	{
		printf("----%d\n", cfg->ceil.b);
		ft_error("Missing data\n");
		return (1);
	}
	return (0);
}

int	check_texture_and_set(t_cfg *cfg, char **s)
{
	int	fd;

	fd = 0;
	if (s[0][0] == 'N')
		fd = open(s[1], O_RDONLY);
	else if (s[0][0] == 'S')
		fd = open(s[1], O_RDONLY);
	else if (s[0][0] == 'W')
		fd = open(s[1], O_RDONLY);
	else if (s[0][0] == 'E')
		fd = open(s[1], O_RDONLY);
	if (fd < 0)
	{
		ft_error("Texture File Error");
		return (1);
	}
	close(fd);
	if (assign_tex(s, cfg))
		return (1);
	return (0);
}
