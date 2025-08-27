/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 07:28:40 by bchapuis          #+#    #+#             */
/*   Updated: 2024/01/30 16:59:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long	res;
	long	sign;

	sign = 1;
	res = 0;
	while ((*str) && ((*str <= 13 && *str >= 9) || *str == ' '))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		if (res != ((res * 10) + (*str - '0')) / 10)
			return ((int)(sign + 1) / 2 / -1);
		res = (res * 10) + (*str - '0');
		str++;
	}
	res = res * sign;
	return (res);
}
