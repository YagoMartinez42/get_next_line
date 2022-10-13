/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:24:38 by samartin          #+#    #+#             */
/*   Updated: 2022/10/13 10:59:57 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*get_next_line(int fd)
{
	char		*line;
	static char	*read_buff;
	static int	buff_pos;
	static int	buff_len;

	line = malloc (sizeof(char));
	if (!line)
		return (NULL);
	*line = '\0';
	if (!read_buff)
	{
		read_buff = malloc(BUFFER_SIZE * (sizeof(char)));
		if (!read_buff)
			return (NULL);
		buff_len = fill_buffer(fd, read_buff);
	}
	while (buff_len > 0 && (!*line || line[gnl_len(line) - 1] != '\n'))
	{
		line = append_chnk(line, read_buff, &buff_pos, buff_len);
		if (buff_pos >= buff_len)
		{
			buff_len = fill_buffer(fd, read_buff);
			buff_pos = 0;
		}
	}
	if (buff_len == -1)
		free(read_buff);
	if (*line == '\0')
		return (NULL);
	else
		return (line);
}
