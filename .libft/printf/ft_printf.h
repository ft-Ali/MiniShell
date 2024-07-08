/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:38:49 by alsiavos          #+#    #+#             */
/*   Updated: 2024/01/10 15:42:38 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft.h"

int	ft_print_hexa(unsigned long nb, char deci);
int	ft_print_usgnint(unsigned int nb);
int	ft_printf(const char *format, ...);
int	ft_print_ptr(long int ptr);
int	ft_print_str(char *str);
int	ft_print_char(char c);
int	ft_print_int(int nb);

#endif
