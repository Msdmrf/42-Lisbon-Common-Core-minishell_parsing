/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:14:44 by migusant          #+#    #+#             */
/*   Updated: 2025/05/27 13:00:37 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

# define HEX_U "0123456789ABCDEF"
# define HEX_L "0123456789abcdef"

int	ft_printf(const char *format, ...);
int	prf_ft_putchar(char c);
int	prf_ft_putstr(char *str);
int	prf_ft_puthex(unsigned long n, char format);
int	prf_ft_putptr(unsigned long ptr);
int	prf_ft_putnbr(unsigned int n, int is_signed);

#endif