/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:25:41 by alsiavos          #+#    #+#             */
/*   Updated: 2023/11/16 13:22:10 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)(s1 + i) != *(unsigned char *)(s2 + i))
			return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
		i++;
	}
	return (0);
}
/*
Comparaison des octets : À chaque itération,
	elle compare les octets correspondants dans les deux zones de mémoire.

Renvoi de la différence en cas de non-égalité : Si un octet diffère 
entre les deux zones de mémoire,
	la fonction renvoie la différence entre les valeurs des octets (s1
	- s2). Cette différence peut être positive, négative ou nulle,
	indiquant l'ordre lexicographique des deux zones de mémoire

*/