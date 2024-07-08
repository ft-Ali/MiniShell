/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 07:59:46 by alsiavos          #+#    #+#             */
/*   Updated: 2023/11/16 13:45:46 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*dest;

	if (size && (nmemb > SIZE_MAX / size))
		return (NULL);
	dest = malloc(size * nmemb);
	if (!dest)
		return (NULL);
	ft_bzero(dest, nmemb * size);
	return (dest);
}

/************
ft_calloc alloue de la mémoire pour un tableau de taille spécifiée,
	s'assure qu'il n'y a pas de dépassement de capacité,
	et initialise la mémoire allouée à zéro avant de 
	renvoyer le pointeur vers cette mémoire.

*************/