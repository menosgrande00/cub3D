/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:36:56 by oonal             #+#    #+#             */
/*   Updated: 2024/10/28 18:27:57 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_char(char *s, unsigned long number, size_t len)
{
	while (number > 0)
	{
		s[len] = (number % 10) + '0';
		number = number / 10;
		len--;
	}
	return (s);
}

static int	ft_intlen(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t			len;
	char			*s;
	int				sign;
	unsigned long	number;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	sign = 1;
	len = ft_intlen(n);
	s = (char *)malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	if (n == 0)
		s[0] = '0';
	if (n < 0)
	{
		sign = -1;
		s[0] = '-';
	}
	number = (unsigned long)(n * sign);
	s[len] = '\0';
	s = ft_char(s, number, len - 1);
	return (s);
}
