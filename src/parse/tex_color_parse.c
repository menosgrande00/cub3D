/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_color_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 18:59:05 by sesimsek          #+#    #+#             */
/*   Updated: 2026/02/07 19:47:17 by oonal            ###   ########.fr       */
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
				ft_error("Color values just can take a number.\n");
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

	if (check_comma_error(s[1]))
	{
		ft_error("Invalid color format (check commas)\n");
		return (1);
	}
	colors = ft_split(s[1], ',');
	if (!colors[2] || colors[3] != NULL)
	{
		ft_error("Wrong color value number. It need to be 3!\n");
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
	char	**sp;
	int		type;
	int		ret;

	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	sp = ft_split(line, ' ');
	type = validate_line_type(sp);
	if (type == -1)
	{
		free_double(sp);
		return (0);
	}
	if (type == 2)
	{
		free_double(sp);
		return (1);
	}
	if (type == 0)
		ret = check_texture_and_set(cfg, sp);
	else
		ret = check_color_and_set(cfg, sp);
	return (free_double(sp), ret);
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
		ft_error("Cub file couldn't open\n");
		return (1);
	}
	if (read_loop(cfg, fd))
		return (1);
	if (check_tex_color_value(cfg))
		return (1);
	return (0);
}
