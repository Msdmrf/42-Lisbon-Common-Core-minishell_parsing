/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:14:30 by migusant          #+#    #+#             */
/*   Updated: 2025/05/27 13:01:13 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static int	prf_ft_format(va_list args, const char format)
{
	if (format == 'c')
		return (prf_ft_putchar(va_arg(args, int)));
	if (format == 's')
		return (prf_ft_putstr(va_arg(args, char *)));
	if (format == 'p')
		return (prf_ft_putptr(va_arg(args, unsigned long)));
	if (format == 'd' || format == 'i')
		return (prf_ft_putnbr(va_arg(args, int), 1));
	if (format == 'u')
		return (prf_ft_putnbr(va_arg(args, unsigned int), 0));
	if (format == 'x' || format == 'X')
		return (prf_ft_puthex(va_arg(args, unsigned int), format));
	if (format == '%')
		return (prf_ft_putchar('%'));
	return (prf_ft_putchar('%') + prf_ft_putchar(format));
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		print_length;
	int		i;

	if (!format || write(1, "", 0) == -1)
		return (-1);
	print_length = 0;
	i = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
			print_length += prf_ft_format(args, format[++i]);
		else
			print_length += prf_ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (print_length);
}
