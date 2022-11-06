/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:13:19 by samartin          #+#    #+#             */
/*   Updated: 2022/11/06 17:53:00 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*append_chnk(char **line, char *buf)
{
	int	i;
	int	line_len;
	int	new_len;

	i = 0;
	line_len = 0;
	if (*buf == 0)
		buf++;
	if (*line)
		line_len = gnl_len(*line);
	while (*(buf + i) && *(buf + i) != '\n')
		i++;
	if (*(buf + i) == '\n')
		i++;
	if (i == 0)
		return (NULL);
	new_len = line_len;
	*line = (char *)realloc(*line, line_len + i + 1);
	//while (new_len < (line_len + i))
	//	new_len += 80;
	//*line = (char *)gnl_mexpand(*line, new_len + 1);
	*line = gnl_strncat(*line, buf, i);
	buf += i;
	return (buf);
}

static char	*fill_buffer(int fd, char *buf, char *buf_start)
{
	int	buff_len;

	if (*buf == '\0')
	{
		buf = buf_start;
		buff_len = read(fd, buf, BUFFER_SIZE);
		if (buff_len < 1)
		{
			free (buf);
			return (NULL);
		}
		buf[buff_len] = '\0';
	}
	return (buf);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buf;
	static char	*buf_start;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!buf)
	{
		buf = malloc((BUFFER_SIZE + 1) * (sizeof(char)));
		if (!buf)
			return (NULL);
		*buf = '\0';
		buf_start = buf;
	}
	line = NULL;
	while (!line || (line[gnl_len(line) - 1] != '\n'))
	{
		buf = fill_buffer(fd, buf, buf_start);
		if (!buf || *(buf) == '\0')
			break ;
		buf = append_chnk(&line, buf);
	}
	return (line);
}
