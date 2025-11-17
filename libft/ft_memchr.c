/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 21:15:49 by oonal             #+#    #+#             */
/*   Updated: 2024/10/28 18:39:07 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		idx;

	idx = 0;
	while (idx < n)
	{
		if (*((unsigned char *)s + idx) == (unsigned char)c)
			return ((void *)s + idx);
		idx++;
	}
	return (NULL);
}
