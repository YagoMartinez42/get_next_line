/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:24:38 by samartin          #+#    #+#             */
/*   Updated: 2022/10/10 17:16:10 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static unsigned int	append_chnk(char *line, char *read_buff, unsigned int pos, \
	unsigned int len)
{
	unsigned int	line_len;
	unsigned int	i;

	i = 0;
	line_len = gnl_len(line);
	while (i < len && read_buff[pos + i] != '\n')
		i++;
	line = (char *)gnl_mexpand(line, (line_len + i + 1));
	line = gnl_strncat(line, &read_buff[pos], i);
	return (pos + i);
}

static unsigned int	fill_buffer(int fd, char *read_buff)
{
	int	buff_len;

	buff_len = read(fd, read_buff, BUFFER_SIZE);
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
		buff_pos = append_chnk(line, read_buff, buff_pos, buff_len);
		if (buff_pos >= buff_len)
			buff_len = fill_buffer(fd, read_buff);
	}
	if (buff_len == -1)
		free(read_buff);
	if (*line == '\0')
		return (NULL);
	else
		return (line);
}

#include <fcntl.h>
#include <stdio.h>

int	main()
{
	int			txt_file;
	char		*line;

	txt_file = open("textfile.txt", O_RDONLY);
	line = get_next_line(txt_file);
	if (!line)
		close(txt_file);
	printf("%s", line);
	return (0);
}
