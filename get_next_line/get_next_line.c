/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 14:54:07 by oonal             #+#    #+#             */
/*   Updated: 2024/12/28 14:54:08 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_after_line(char *perm)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (perm[i] != '\0' && perm[i] != '\n')
		i++;
	if (!perm[i])
	{
		free (perm);
		return (NULL);
	}
	str = malloc(ft_strlen(perm) - i + 1);
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (perm[i])
		str[j++] = perm[i++];
	str[j] = '\0';
	free (perm);
	return (str);
}

char	*ft_one_line(char	*perm)
{
	int		i;
	char	*line;

	i = 0;
	while (perm[i] != '\n' && perm[i] != '\0')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (perm[i] != '\n' && perm[i] != '\0')
	{
		line[i] = perm[i];
		i++;
	}
	if (perm[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_find_n(char	*perm, int fd)
{
	char	*line;
	ssize_t	r;

	line = ft_calloc(1, BUFFER_SIZE + 1);
	r = 1;
	while (!ft_strchr(line, '\n') && r > 0)
	{
		r = read(fd, line, BUFFER_SIZE);
		if (r == -1 || (r == 0 && (!perm || *perm == '\0')))
		{
			free (line);
			free (perm);
			return (NULL);
		}
		line[r] = '\0';
		perm = ft_strjoin(perm, line);
	}
	free (line);
	return (perm);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*perm;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	perm = ft_find_n(perm, fd);
	if (!perm)
	{
		free (perm);
		return (NULL);
	}
	line = ft_one_line(perm);
	perm = ft_after_line(perm);
	return (line);
}
