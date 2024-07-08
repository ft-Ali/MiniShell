/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:15:10 by alsiavos          #+#    #+#             */
/*   Updated: 2023/11/16 16:37:06 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*dest;

	i = 0;
	if (!s || !f)
		return (NULL);
	dest = malloc(ft_strlen(s) + 1 * (sizeof(char)));
	if (!dest)
		return (NULL);
	while (s[i])
	{
		dest[i] = (*f)(i, s[i]);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/*
Application de la fonction à chaque caractère
Retour du pointeur vers la nouvelle chaîne
Cette fonction est utile lorsque vous souhaitez appliquer une
opération spécifique à chaque caractère d'une chaîne,
en tenant compte de leur position dans la chaîne,
et obtenir une nouvelle chaîne résultante

*/