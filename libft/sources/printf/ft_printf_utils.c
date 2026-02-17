/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:31:46 by migusant          #+#    #+#             */
/*   Updated: 2025/05/27 13:02:03 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int	prf_ft_putchar(char c)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	return (1);
}

int	prf_ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (prf_ft_putstr("(null)"));
	while (str[i])
	{
		prf_ft_putchar(str[i]);
		i++;
	}
	return (i);
}

int	prf_ft_putnbr(unsigned int n, int is_signed)
{
	int	len;

	len = 0;
	if (is_signed && (int)n < 0)
	{
		if ((int)n == -2147483648)
			return (prf_ft_putstr("-2147483648"));
		len += prf_ft_putchar('-');
		n = -(int)n;
	}
	if (n >= 10)
		len += prf_ft_putnbr(n / 10, 0);
	len += prf_ft_putchar((n % 10) + '0');
	return (len);
}

int	prf_ft_puthex(unsigned long n, char format)
{
	int	len;

	len = 0;
	if (n >= 16)
		len += prf_ft_puthex(n / 16, format);
	if (format == 'x')
		len += prf_ft_putchar(HEX_L[n % 16]);
	else if (format == 'X')
		len += prf_ft_putchar(HEX_U[n % 16]);
	return (len);
}

int	prf_ft_putptr(unsigned long ptr)
{
	int	len;

	len = 0;
	if (!ptr)
		return (prf_ft_putstr("(nil)"));
	len += prf_ft_putstr("0x");
	len += prf_ft_puthex(ptr, 'x');
	return (len);
}
