/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 21:12:17 by oonal             #+#    #+#             */
/*   Updated: 2024/10/28 16:57:44 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			idx;
	unsigned char	c1;
	unsigned char	c2;

	idx = 0;
	while (idx < n)
	{
		c1 = *((unsigned char *)s1 + idx);
		c2 = *((unsigned char *)s2 + idx);
		if (c1 != c2)
			return (c1 - c2);
		idx++;
	}
	return (0);
}
