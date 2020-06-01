/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 02:19:51 by asimoes           #+#    #+#             */
/*   Updated: 2020/06/01 17:52:58 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

typedef struct	s_fd_data
{
	int				fd;
	char			*buf;
	int				size;
	short int		eof;
	void			*next;
}				t_fd_data;

char	*ft_strndup(const char *str, unsigned int n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strnchr(const char *s, int c, int len);
void	*ft_realloc(void *ptr, size_t size, size_t ptrsize);
int		remove_fd_data(t_fd_data *fd_data);

int		process_buffer(char **buffer, char **line, int *bufsize, int c);
int		free_buffers(char *readbuf, char **buf);
int		get_next_line(int fd, char **line);
int		get_next_line_r(t_fd_data **fd_data, int fd, char **line);

#endif
