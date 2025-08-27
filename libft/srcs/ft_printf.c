/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 07:57:30 by bchapuis          #+#    #+#             */
/*   Updated: 2024/01/31 10:49:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_format(const char *str, va_list args)
{
	int	len;

	len = 0;
	if (*str == 'c')
		len += ft_putchar(va_arg(args, int));
	else if (*str == 's')
		len += ft_putstr(va_arg(args, char *));
	else if (*str == 'p')
		len += ft_ptr(va_arg(args, unsigned long), "0123456789abcdef");
	else if (*str == 'd' || *str == 'i')
		len += ft_putnbr(va_arg(args, int));
	else if (*str == 'u')
		len += ft_putunsignnbr(va_arg(args, unsigned int));
	else if (*str == 'x')
		len += ft_puthexanbr(va_arg(args, unsigned int), "0123456789abcdef");
	else if (*str == 'X')
		len += ft_puthexanbr(va_arg(args, unsigned int), "0123456789ABCDEF");
	else if (*str == '%')
		len += ft_putchar('%');
	return (len);
}

int	ft_printf(const char *str, ...)
{
	int		len;
	va_list	args;

	len = 0;
	if (str == NULL)
		return (len);
	va_start(args, str);
	while (*str)
	{
		if (*str == '%' && str)
		{
			str++;
			len += ft_format(str, args);
		}
		else
			len += ft_putchar(*str);
		str++;
		if (len == -1)
		{
			break ;
			return (-1);
		}
	}
	va_end(args);
	return (len);
}
