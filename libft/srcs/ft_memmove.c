/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchapuis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 08:36:56 by bchapuis          #+#    #+#             */
/*   Updated: 2023/11/14 08:36:58 by bchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;

	if (dest == NULL && src == NULL)
		return (NULL);
	d = (char *)dest;
	s = (char *)src;
	if (s < d)
	{
		s = s + n - 1;
		d = d + n - 1;
		while (n > 0)
		{
			*d-- = *s--;
			n--;
		}
	}
	else
	{
		while (n-- > 0)
		{
			*d++ = *s++;
		}
	}
	return (dest);
}
