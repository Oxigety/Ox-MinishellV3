/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_err_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfreydie <tfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:31:36 by tfreydie          #+#    #+#             */
/*   Updated: 2024/06/06 17:47:22 by tfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void			ft_recursive_print(unsigned long long ptr, int *size,
						char buffer[BUFFER_SIZE]);
static unsigned int	ft_base_length(char *base);

void	ft_putnbr_err(int nbr, int *size, char buffer[BUFFER_SIZE])
{
	long long	real_nbr;
	int			digit;

	real_nbr = nbr;
	if (real_nbr < 0 && *size != -1)
	{
		real_nbr *= -1;
		ft_putncount_char_err('-', size, buffer);
	}
	if (real_nbr >= 10 && *size != -1)
	{
		ft_putnbr_err(real_nbr / 10, size, buffer);
		ft_putnbr_err(real_nbr % 10, size, buffer);
	}
	else if (real_nbr < 10 && *size != -1)
	{
		digit = real_nbr + '0';
		ft_putncount_char_err(digit, size, buffer);
	}
}

void	ft_print_ptr_err(unsigned long long ptr, int *size,
			char buffer[BUFFER_SIZE])
{
	if (ptr == 0)
		ft_putncount_str_err("(nil)", size, buffer);
	else
	{
		ft_putncount_str_err("0x", size, buffer);
		ft_recursive_print(ptr, size, buffer);
	}
}

static void	ft_recursive_print(unsigned long long ptr, int *size,
				char buffer[BUFFER_SIZE])
{
	char	*base;

	base = "0123456789abcdef";
	if (ptr >= 16 && *size != -1)
	{
		ft_recursive_print(ptr / 16, size, buffer);
		ft_recursive_print(ptr % 16, size, buffer);
	}
	else if (ptr < 16 && *size != -1)
		ft_putncount_char_err(base[ptr], size, buffer);
}

void	uns_2(unsigned int nbr, char *base, int *size,
			char buffer[BUFFER_SIZE])
{
	unsigned int		base_len;

	base_len = ft_base_length(base);
	if (nbr >= base_len && *size != -1)
	{
		uns_2(nbr / base_len, base, size, buffer);
		uns_2(nbr % base_len, base, size, buffer);
	}
	else if (nbr < base_len && *size != -1)
		ft_putncount_char_err(base[nbr], size, buffer);
}

static unsigned int	ft_base_length(char *base)
{
	int	i;

	i = 0;
	while (base[i] != '\0')
		i++;
	return (i);
}
