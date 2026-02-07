/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 19:00:47 by sesimsek          #+#    #+#             */
/*   Updated: 2026/02/07 19:39:49 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

void	free_double(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
}

int	in_range(int v)
{
	if (v >= 0 && v <= 255)
		return (1);
	else
		return (0);
}

int	validate_line_type(char **sp)
{
	if (!sp || !sp[0])
		return (-1);
	if (!sp[1])
	{
		ft_error("Missing value or path\n");
		return (2);
	}
	if (sp[2])
	{
		ft_error("Extra value in line\n");
		return (2);
	}
	if (!ft_strcmp(sp[0], "NO") || !ft_strcmp(sp[0], "SO")
		|| !ft_strcmp(sp[0], "WE") || !ft_strcmp(sp[0], "EA"))
		return (0);
	if (!ft_strcmp(sp[0], "F") || !ft_strcmp(sp[0], "C"))
		return (1);
	ft_error("Invalid identifier\n");
	return (2);
}
