/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfreydie <tfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 17:09:05 by tfreydie          #+#    #+#             */
/*   Updated: 2024/05/30 02:59:40 by tfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_printf2(const char *text, ...)
{
	va_list	argptr;
	size_t	i;
	int		actual_size;
	char	buffer[BUFFER_SIZE];

	va_start(argptr, text);
	actual_size = 0;
	i = 0;
	if (!text || write(2, NULL, 0) == -1)
		actual_size = -1;
	while (text[i] && actual_size != -1)
	{
		if (text[i] == '%')
		{
			i++;
			ft_special_char_err(text[i], argptr, &actual_size, buffer);
		}
		else
			ft_putncount_char_err(text[i], &actual_size, buffer);
		i++;
	}
	va_end(argptr);
	if (actual_size != -1)
		return (write(2, buffer, actual_size));
	return (actual_size);
}

void	ft_special_char_err(char c, va_list argptr, int *size,
			char buffer[BUFFER_SIZE])
{
	if (c == 'c')
		ft_putncount_char_err(va_arg(argptr, int), size, buffer);
	else if (c == 's')
		ft_putncount_str_err(va_arg(argptr, char *), size, buffer);
	else if (c == 'p')
		ft_print_ptr_err(va_arg(argptr, unsigned long long), size, buffer);
	else if (c == 'd')
		ft_putnbr_err(va_arg(argptr, int), size, buffer);
	else if (c == 'i')
		ft_putnbr_err(va_arg(argptr, int), size, buffer);
	else if (c == 'u')
		uns_2(va_arg(argptr, unsigned int), "0123456789", size, buffer);
	else if (c == 'x')
		uns_2(va_arg(argptr, unsigned int), "0123456789abcdef", size, buffer);
	else if (c == 'X')
		uns_2(va_arg(argptr, unsigned int), "0123456789ABCDEF", size, buffer);
	else if (c == '%')
		ft_putncount_char_err('%', size, buffer);
	else if (c == '\0')
		*size = -1;
	else
	{
		ft_putncount_char_err('%', size, buffer);
		ft_putncount_char_err(c, size, buffer);
	}
}

void	ft_putncount_char_err(char c, int *size, char buffer[BUFFER_SIZE])
{
	buffer[*size] = c;
	*size += 1;
}

void	ft_putncount_str_err(char *str, int *size, char buffer[BUFFER_SIZE])
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		ft_putncount_str_err("(null)", size, buffer);
		return ;
	}
	while (str[i])
	{
		ft_putncount_char_err(str[i], size, buffer);
		i++;
	}
	return ;
}
