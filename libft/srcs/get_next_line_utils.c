/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Oxigety_ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:46:28 by Oxigety_          #+#    #+#             */
/*   Updated: 2023/11/30 17:58:31 by Oxigety_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/libft.h"

size_t	ft_strlen2(const char *s, size_t n)
{
	size_t	i;
	size_t	cpt;

	i = n;
	cpt = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		cpt++;
		i++;
	}
	return (cpt);
}

void	ft_bzero2(void *s, size_t n)
{
	while (n > 0 && *(char *)s)
	{
		n--;
		*(char *)s = '\0';
		s++;
	}
}

char	*alloc_join(char const *s1, char const *s2)
{
	char	*str;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		str = malloc(sizeof(char) * (ft_strlen2(s2, 0) + 1));
	else
		str = malloc(sizeof(char) * (ft_strlen2(s1, 0)
					+ ft_strlen2(s2, 0)) + 1);
	return (str);
}

char	*ft_strjoin2(char const *s1, char const *s2)
{
	size_t		i;
	char		*str;

	i = 0;
	str = alloc_join(s1, s2);
	if (str == NULL)
	{
		free((char *)s1);
		return (NULL);
	}
	while (s1 != NULL && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (*s2)
	{
		str[i] = *s2;
		s2++;
		i++;
	}
	free((char *)s1);
	str[i] = '\0';
	return (str);
}

void	*ft_memmove2(void *dest, const void *src, size_t n)
{
	char			*adddest;
	char			*addsrc;
	size_t			i;

	i = 0;
	adddest = (char *)dest;
	addsrc = (char *)src;
	if (n == 0 || adddest == addsrc)
		return (dest);
	if (adddest < addsrc)
	{
		while (i < n)
		{
			adddest[i] = addsrc[i];
			i++;
		}
	}
	else
	{
		while (n--)
			adddest[n] = addsrc[n];
	}
	return (adddest);
}
