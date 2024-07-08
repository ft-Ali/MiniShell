/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:38:06 by alsiavos          #+#    #+#             */
/*   Updated: 2024/01/10 16:04:13 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_checkarg(char li, va_list ap)
{
	int	result;

	result = 0;
	if (li == 'c')
		result += ft_print_char(va_arg(ap, int));
	else if (li == 's')
		result += ft_print_str(va_arg(ap, char *));
	else if (li == 'd' || li == 'i')
		result += ft_print_int(va_arg(ap, long int));
	else if (li == 'u')
		result += ft_print_usgnint(va_arg(ap, unsigned int));
	else if (li == 'x' || li == 'X')
		result += ft_print_hexa(va_arg(ap, unsigned int), li);
	else if (li == 'p')
		result += ft_print_ptr(va_arg(ap, long int));
	else if (li == '%')
		result += ft_print_char('%');
	return (result);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (!format)
		return (-1);
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			count += ft_checkarg(format[i + 1], ap);
			i++;
		}
		else
		{
			count += write(1, &format[i], 1);
		}
		i++;
	}
	va_end(ap);
	return (count);
}
