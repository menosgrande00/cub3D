/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_color_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 18:59:05 by sesimsek          #+#    #+#             */
/*   Updated: 2026/01/10 15:56:49 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	process_color_values(t_cfg *cfg, char **colors, char *type)
{
	int		i;
	int		j;
	char	*trimmed;

	i = -1;
	while (colors[++i])
	{
		trimmed = ft_strtrim(colors[i], " ");
		free(colors[i]);
		colors[i] = trimmed;
		j = -1;
		while (colors[i][++j])
		{
			if (!ft_isdigit(colors[i][j]))
			{
				ft_error("Color values just can take a number.");
				return (1);
			}
		}
		set_color(cfg, type, colors, i);
	}
	return (0);
}

int	check_color_and_set(t_cfg *cfg, char **s)
{
	char	**colors;

	colors = ft_split(s[1], ',');
	if (!colors[2] || colors[3] != NULL)
	{
		ft_error("Wrong color value number. It need to be 3!");
		free_double(colors);
		return (1);
	}
	if (process_color_values(cfg, colors, s[0]))
	{
		free_double(colors);
		return (1);
	}
	free_double(colors);
	return (0);
}

int	check_line(t_cfg *cfg, char *line)
{
	char	**split;
	int		ret;

	ret = 0;
	line[ft_strlen(line) - 1] = '\0';
	split = ft_split(line, ' ');
	if (split[2])
	{
		free_double(split);
		ft_error("Extra value in line in file");
		return (1);
	}
	if (!ft_strcmp(split[0], "NO") || !ft_strcmp(split[0], "SO")
		|| !ft_strcmp(split[0], "WE") || !ft_strcmp(split[0], "EA"))
		ret = check_texture_and_set(cfg, split);
	else if (!ft_strcmp(split[0], "F") || !ft_strcmp(split[0], "C"))
		ret = check_color_and_set(cfg, split);
	else
	{
		free_double(split);
		ft_error("Texture, Floor or Ceil name is wrong!");
		return (1);
	}
	free_double(split);
	return (ret);
}

static int	read_loop(t_cfg *cfg, int fd)
{
	int		i;
	char	*line;

	i = 0;
	while (i <= 5)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return (1);
		else if (line[0] == '\n')
		{
			free(line);
			continue ;
		}
		if (check_line(cfg, line))
		{
			free(line);
			return (1);
		}
		i++;
		free(line);
	}
	return (0);
}

int	set_tex_color_lines(t_cfg *cfg, int fd)
{
	if (fd < 0)
	{
		ft_error("Cub file couldn't open");
		return (1);
	}
	if (read_loop(cfg, fd))
		return (1);
	if (check_tex_color_value(cfg))
		return (1);
	return (0);
}
