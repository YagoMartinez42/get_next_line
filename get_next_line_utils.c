/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:24:47 by samartin          #+#    #+#             */
/*   Updated: 2022/10/10 17:16:12 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	*gnl_memcpy(void *dst, const void *src, unsigned int n)
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

void	*gnl_mexpand(void *ptr, unsigned int size)
{
	void	*ret_ptr;

	if (!ptr)
		return (NULL);
	ret_ptr = malloc(size * sizeof(char));
	if (!ret_ptr)
		return (NULL);
	gnl_memcpy (ret_ptr, ptr, size);
	free (ptr);
	return (ret_ptr);
}

unsigned int	gnl_len(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*gnl_strncat(char *dest, char *src, unsigned int nb)
{
	unsigned int	pos1;
	unsigned int	pos2;

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
	dest[pos1] = 0;
	return (dest);
}
