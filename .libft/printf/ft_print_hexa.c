/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:38:22 by alsiavos          #+#    #+#             */
/*   Updated: 2024/01/10 16:04:13 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hexa(unsigned long nb, char deci)
{
	int		count;
	char	*deci_min;
	char	*deci_max;

	count = 0;
	deci_min = "0123456789abcdef";
	deci_max = "0123456789ABCDEF";
	if (nb >= 16)
	{
		count += ft_print_hexa(nb / 16, deci);
		count += ft_print_hexa(nb % 16, deci);
	}
	else if (nb < 16 && deci == 'x')
		count += ft_print_char(deci_min[nb]);
	else if (nb < 16 && deci == 'X')
		count += ft_print_char(deci_max[nb]);
	return (count);
}
