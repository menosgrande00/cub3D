#include "../inc/cub3d.h"

static void	line_alloc(char ***s, int n, int *capacity)
{
	int		temp;
	char	**str_temp;
	int		i;

	i = -1;
	if (n + 1 >= *capacity)
	{
		if (*capacity == 0)
			temp = 16;
		else
			temp = 2 * (*capacity);
		str_temp = (char **)malloc(sizeof(char *) * temp);
		while (++i < n)
			str_temp[i] = (*s)[i];
		if (*s)
			free(*s);
		*s = str_temp;
		*capacity = temp;
	}
}

static void	map_start(int fd, char ***lines, int *h, char *str)
{
	char	**s;
	int		n;
	int		capacity;

	s = NULL;
	capacity = 0;
	n = 0;
	while(1)
	{
		trim_newline(str);
		if (is_line_blank(str))
		{
			free(str);
			break;
		}
		line_alloc(&s, n, &capacity);
		s[n++] = str;
		s[n] = NULL;
		str = get_next_line(fd);
		if (str == NULL)
			break;
	}
	*lines = s;
	*h = n;
}

int	collect_map_lines(int fd, char ***lines, int *h)
{
	char	*str;

	str = get_next_line(fd);
	*lines = NULL;
	while (str)
	{
		if (!is_line_blank(str))
			break;
		free(str);
		str = get_next_line(fd);
	}
	if (!str)
	{
		ft_error("No map!");
		return (1);
	}
	map_start(fd, lines, h, str);
	return (0);
}
