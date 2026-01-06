/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesimsek <sesimsek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 19:01:34 by sesimsek          #+#    #+#             */
/*   Updated: 2026/01/06 20:39:50 by sesimsek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_line_blank(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\r' && s[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

void	trim_newline(char *s)
{
	int	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	if (len > 0 && s[len - 1] == '\n')
		s[len - 1] = '\0';
}

int	is_allowed_char(char c)
{
	if (c == '0' || c == '1' || c == ' ' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}
