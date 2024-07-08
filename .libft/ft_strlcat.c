/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:25:20 by alsiavos          #+#    #+#             */
/*   Updated: 2023/11/16 16:35:03 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	srclen;
	size_t	dstlen;

	if (!dst && size == 0)
		return (0);
	srclen = ft_strlen((char *)src);
	dstlen = ft_strlen((char *)dst);
	i = 0;
	j = dstlen;
	if (dstlen < size - 1 && size > 0)
	{
		while (src[i] && dstlen + i < size - 1)
			dst[j++] = src[i++];
		dst[j] = '\0';
	}
	if (size <= dstlen)
		dstlen = size;
	return (srclen + dstlen);
}
/*
Cette fonction est utilisée pour concaténer
 deux chaînes de caractères tout en évitant
  les débordements de tampon
*/