/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 02:19:51 by asimoes           #+#    #+#             */
/*   Updated: 2020/05/26 14:33:31 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# define BUFFER_SIZE 1024

static char			*ft_strndup(const char *str, unsigned int n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
char				*ft_strnchr(const char *s, int c, int len);
void				*ft_realloc(void *ptr, size_t size, size_t ptrsize);

int					get_next_line(int fd, char **line);
int					get_next_line_r(int fd, char **line, char **buffer, int *bufsize);

#endif