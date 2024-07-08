/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:40:54 by alsiavos          #+#    #+#             */
/*   Updated: 2023/11/16 13:33:31 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}
/*
La fonction ft_striteri est utile lorsque vous souhaitez
 appliquer une opération spécifique à chaque caractère d'une chaîne,
en tenant compte de leur position dans la chaîne.
 Cela peut être utile pour effectuer des manipulations sur la chaîne,
par exemple,
la modification de certains caractères en fonction de leur position.
*/