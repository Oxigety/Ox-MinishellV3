/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchapuis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:10:13 by bchapuis          #+#    #+#             */
/*   Updated: 2023/11/23 09:57:30 by bchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int search)
{
	size_t	len;

	len = ft_strlen(s);
	if (s[len] == (unsigned char)search)
		return (((char *)s) + len);
	while (len-- > 0)
	{
		if (s[len] == (unsigned char)search)
			return (((char *)s) + len);
	}
	return (0);
}
