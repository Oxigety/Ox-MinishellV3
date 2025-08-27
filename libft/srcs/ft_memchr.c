/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchapuis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:30:07 by bchapuis          #+#    #+#             */
/*   Updated: 2023/11/21 10:12:10 by bchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *str, int search, size_t n)
{
	char	*s;

	s = (char *)str;
	while (n--)
		if (*s++ == (char)search)
			return (s - 1);
	return (NULL);
}
