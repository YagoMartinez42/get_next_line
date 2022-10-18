/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:24:38 by samartin          #+#    #+#             */
/*   Updated: 2022/10/18 12:53:33 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "get_next_line.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

static void	*gnl_memcpy(void *dst, const void *src, int n)
{
	void	*ret;

	if (dst == NULL || src == NULL)
		return (NULL);
	ret = dst;
	while (n > 0)
	{
		*(unsigned char *)dst = *(unsigned char *)src;
		dst++;
		src++;
		n--;
	}
	return (ret);
}

void	*gnl_mexpand(void *ptr, int size)
{
	void	*ret_ptr;

	if (!ptr)
		return (NULL);
	ret_ptr = malloc(size * sizeof(char));
	if (!ret_ptr)
		return (NULL);
	gnl_memcpy(ret_ptr, ptr, size);
	free (ptr);
	return (ret_ptr);
}

int	gnl_len(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*gnl_strncat(char *dest, char *src, int nb)
{
	int	pos1;
	int	pos2;

	pos1 = 0;
	pos2 = 0;
	while (dest[pos1] != 0)
		pos1++;
	while (src[pos2] != 0 && pos2 < nb)
	{
		dest[pos1] = src[pos2];
		pos1++;
		pos2++;
	}
	dest[pos1] = '\0';
	return (dest);
}




static char	*append_chnk(char *line, char *read_buff, int *buff_pos, \
	int buff_len)
{
	int	line_len;
	int	i;

	i = 0;
	line_len = gnl_len(line);
	while ((*buff_pos + i) < (buff_len - 1) && read_buff[*buff_pos + i] != '\n')
		i++;
	line = (char *)gnl_mexpand(line, (line_len + i + 1));
	gnl_strncat(line, &read_buff[*buff_pos], i + 1);
	*buff_pos = *buff_pos + i + 1;
	return (line);
}

static int	fill_buffer(int fd, char *read_buff)
{
	int	buff_len;

	buff_len = read(fd, read_buff, BUFFER_SIZE);
	read_buff[buff_len] = '\0';
	return (buff_len);
}

static int	initialize(char **line, char **read_buff, int buff_len, int fd)
{
	*line = malloc (sizeof(char));
	if (!*line)
		return (0);
	**line = '\0';
	if (!*read_buff)
	{
		*read_buff = malloc(BUFFER_SIZE * (sizeof(char)));
		if (!*read_buff)
		{
			free (*line);
			return (0);
		}
		buff_len = fill_buffer(fd, *read_buff);
		if (buff_len < 1)
			return (0);
	}
	return (buff_len);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*read_buff;
	static int	buff_pos;
	static int	buff_len;

	buff_len = initialize(&line, &read_buff, buff_len, fd);
	if (!buff_len)
		return (NULL);
	while (!*line || (line[gnl_len(line) - 1] != '\n'))
	{
		line = append_chnk(line, read_buff, &buff_pos, buff_len);
		if (buff_pos >= buff_len)
		{
			buff_len = fill_buffer(fd, read_buff);
			if (buff_len == 0)
			{
				free (read_buff);
				return (line);
			}
			buff_pos = 0;
		}
	}
	if (buff_len == 0 && read_buff)
		free(read_buff);
	if (*line == '\0')
	{
		free(line);
		if (read_buff)
			free(read_buff);
		return (NULL);
	}
	else
		return (line);
}


#include <stdio.h>

int main (void)
{
	int		fd;
	char	*line;

	fd = open("textfile.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
//	system("leaks a.out");
}