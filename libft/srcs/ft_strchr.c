/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchapuis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:55:33 by bchapuis          #+#    #+#             */
/*   Updated: 2023/11/23 09:56:55 by bchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr( const char *s, int search)
{
	if (s[0] == (unsigned char)search)
		return ((char *)s);
	while (*s)
	{
		s++;
		if (*s == (unsigned char)search)
			return ((char *)s);
	}
	return (0);
}
