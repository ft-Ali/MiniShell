/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:35:29 by alsiavos          #+#    #+#             */
/*   Updated: 2023/11/16 16:36:48 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srcsize;
	size_t	i;

	srcsize = ft_strlen((char *)src);
	i = 0;
	if (size != 0)
	{
		while (src[i] != '\0' && i < (size - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srcsize);
}
/*
Cette fonction est utilisée pour copier une chaîne de caractères source (src)
 dans une chaîne de destination (dst), tout en garantissant qu'au plus size - 1
  caractères de la source sont copiés dans la destination. La fonction renvoie
   la longueur totale de la chaîne source,
	indépendamment de la taille de la destination
*/