/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchapuis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:20:14 by bchapuis          #+#    #+#             */
/*   Updated: 2023/11/21 10:09:05 by bchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp( const char *first, const char *second, size_t length )
{
	size_t	i;

	i = 0;
	while (first[i] && second[i] && (first[i] == second[i]) && i < (length - 1))
	{
		i++;
	}
	if (length < 1)
		return (0);
	return ((unsigned char)first[i] - (unsigned char)second[i]);
}
