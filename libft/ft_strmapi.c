/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 21:50:14 by oonal             #+#    #+#             */
/*   Updated: 2024/10/28 17:15:36 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	size_t	idx;
	char	*tmp;
	size_t	len;

	if (!s || !f)
		return (NULL);
	len = ft_strlen((char *)s) + 1;
	tmp = (char *)malloc(sizeof(char) * len);
	if (!tmp)
		return (NULL);
	idx = 0;
	while (idx < len - 1)
	{
		tmp[idx] = f(idx, s[idx]);
		idx++;
	}
	tmp[idx] = '\0';
	return (tmp);
}
