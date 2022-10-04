/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:24:47 by samartin          #+#    #+#             */
/*   Updated: 2022/10/04 18:57:56 by samartin         ###   ########.fr       */
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

void	*gnl_realloc(void *ptr, unsigned int size)
{
	char	*ret_ptr;
	void	*ret_ptr;

	if (!ptr)
		return(NULL);
	ret_ptr = malloc(size * sizeof(char));
	if (!ret_ptr)
		return(NULL);
	gnl_memcpy (ret_ptr, ptr, size);
	free (ptr);
	return ((void *)ret_ptr);
}
