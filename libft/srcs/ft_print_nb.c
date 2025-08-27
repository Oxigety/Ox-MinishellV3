/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 07:58:06 by bchapuis          #+#    #+#             */
/*   Updated: 2024/01/31 10:49:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		len += 1;
		ft_putchar('-');
		if (n == -2147483648)
		{
			ft_putchar('2');
			len += 1;
			n = -147483648;
		}
		n *= -1;
	}
	if (n / 10)
		len += ft_putnbr(n / 10);
	len += ft_putchar(n % 10 + '0');
	return (len);
}

int	ft_putunsignnbr(unsigned int n)
{
	int	len;

	len = 0;
	if (n / 10)
		len += ft_putunsignnbr(n / 10);
	len += ft_putchar(n % 10 + '0');
	return (len);
}

int	ft_puthexanbr(unsigned long n, char *str)
{
	int	i;

	i = 0;
	if (n >= 16)
		i += ft_puthexanbr((n / 16), str);
	i += ft_putchar(str[(n % 16)]);
	return (i);
}

int	ft_ptr(unsigned long n, char *str)
{
	int	i;

	if (n == 0)
	{
		i = ft_putstr("(nil)");
		return (i);
	}
	i = 2;
	write (1, "0x", 2);
	i += ft_puthexanbr(n, str);
	return (i);
}
