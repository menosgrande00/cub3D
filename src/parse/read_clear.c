#include "../inc/cub3d.h"

int is_writed_two_times(char **split, t_cfg *cfg)
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

int	set_color(t_cfg *cfg, char *first, char **colors, int i)
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
	if (!in_range(cfg->floor.r) || !in_range(cfg->floor.g)
			|| !in_range(cfg->floor.b) || !in_range(cfg->ceil.r)
			|| !in_range(cfg->ceil.g) || !in_range(cfg->ceil.b))
	{
		ft_error("RGB colors have to between 0 to 255!");
		return (1);
	}
	return (0);
}

int		check_color_and_set(t_cfg *cfg, char **s)
{
	char	**colors;
	int		i;
	int		j;

	i = -1;
	colors = ft_split(s[1], ',');
	if (!colors[2])
	{
		ft_error("Missing colors");
		free_double(colors);
		return(1);
	}
	while (colors[++i])
	{
		colors[i] = ft_strtrim(colors[i], " ");
		j = -1;
		while(colors[i][++j])
		{
			if(!ft_isdigit(colors[i][j]))
			{
				free_double(colors);
				ft_error("Color values just can take a number.");
				return (1);
			}
		}
		if (set_color(cfg, s[0], colors, i))
		{
			free_double(colors);
			return (1);
		}
	}
	free_double(colors);
	return (0);
}

int		check_texture_and_set(t_cfg *cfg, char **s)
{
	int fd;

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

int		check_line(t_cfg *cfg, char *line)
{
	char	**split;
	int		ret;

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
	if (ret)
	{
		free_double(split);
		return (1);
	}
	free_double(split);
	return (0);
}

int		set_tex_color_lines(t_cfg *cfg, int	fd)
{
	int		i;
	char	*line;

	i = 0;
	if (fd < 0)
	{
		ft_error("Cub file couldn't open");
		return (1);
	}
	while(i <= 5)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return (1);
		else if (line[0] == '\n')
			continue ;
		else
			if (check_line(cfg, line))
			{
				free(line);
				return (1);
			}
			i++;
		free(line);
	}
	if (!cfg->no || !cfg->so || !cfg->we || !cfg->ea || !cfg->floor.r
			|| !cfg->floor.g || !cfg->floor.b || !cfg->ceil.r
			|| !cfg->ceil.g || !cfg->ceil.b)
	{
		ft_error("Missing data");
		free(line);
		return (1);
	}
	return (0);
}
