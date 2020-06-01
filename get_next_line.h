/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 02:19:51 by asimoes           #+#    #+#             */
/*   Updated: 2020/06/01 22:29:06 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# define ERR_BUFFER_NULL -1
# define ERR_NO_LINE -2
# define ERR_MALLOC -3
# define ERR_READ_FAILURE -4

typedef struct	s_fd_data
{
	int				fd;
	char			*buf;
	int				size;
	short int		eof;
	void			*next;
}				t_fd_data;

char			*ft_strndup(const char *str, unsigned int n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
char			*ft_strnchr(const char *s, int c, int len);
void			*ft_realloc(void *ptr, size_t size, size_t ptrsize);

t_fd_data		*get_fd_data(t_fd_data **start, int fd);
t_fd_data		*add_fd_data(t_fd_data **start, int fd);
int				remove_fd_data(t_fd_data *fd_data, t_fd_data **start);

int				get_line(t_fd_data *d, char **line, t_fd_data **start);
int				read_loop(t_fd_data *d, char **line, t_fd_data **start);

int				get_next_line(int fd, char **line);

#endif
