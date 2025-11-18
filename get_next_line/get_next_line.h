/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omerfarukonal <omerfarukonal@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 14:54:14 by oonal             #+#    #+#             */
/*   Updated: 2025/11/18 14:28:45 by omerfarukon      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
char	*ft_after_line(char *perm);
char	*ft_find_n(char	*perm, int fd);
char	*ft_one_line(char *perm);

size_t	ft_strlenn(const char *str);
char	*ft_strchrs(const char *str, int ch);
char	*ft_strjoinn(char *s1, char *s2);
void	ft_bzeroo(void *s, size_t n);
void	*ft_callocc(size_t count, size_t size);

#endif
