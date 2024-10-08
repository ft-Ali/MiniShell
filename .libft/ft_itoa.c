/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:58:30 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/03 15:12:24 by jpointil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(long int nbr)
{
	int	len;

	if (nbr <= 0)
		len = 1;
	else
		len = 0;
	while (nbr != 0)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

static long long	ft_abs(long long n)
{
	long long	nb;

	if (n < 0)
		nb = -n;
	else
		nb = n;
	return (nb);
}

static char	*ft_mallocstr(size_t nbr)
{
	char	*str;

	str = malloc(sizeof(char) * (nbr + 1));
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_itoa(int nbr)
{
	int				len;
	int				sign;
	unsigned int	nb;
	char			*str;

	sign = 42;
	if (nbr < 0)
		sign = -1;
	len = ft_len(nbr);
	str = ft_mallocstr(len);
	if (!str)
		return (NULL);
	str[len] = '\0';
	len--;
	nb = ft_abs(nbr);
	while (len >= 0)
	{
		str[len] = nb % 10 + 48;
		nb = nb / 10;
		len--;
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}

/*

ft_len : Cette fonction calcule la longueur d'un nombre en comptant 
le nombre de chiffres. 
Elle initialise la longueur à 1 si le nombre est 0 ou négatif,
	sinon à 0.
ft_abs : Cette fonction renvoie la valeur absolue d'un nombre.

ft_mallocstr : Cette fonction alloue de la mémoire pour une chaîne
de caractères de taille spécifiée.

ft_itoa : Cette fonction principale convertit un entier en une
chaîne de caractères.
Elle détermine le signe du nombre,
	alloue de la mémoire pour la chaîne résultante,
	convertit le nombre en chaîne en inversant les chiffres,
	et ajoute le signe '-' si le nombre est négatif.


*/