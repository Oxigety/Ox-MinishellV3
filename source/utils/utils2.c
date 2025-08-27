/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Oxigety_ <Oxigety_@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:14:14 by Oxigety_          #+#    #+#             */
/*   Updated: 2024/07/19 11:14:14 by Oxigety_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*alloc_join(char const *s1, char const *s2)
{
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	return (str);
}

char	*ft_strjoin_f(char *s1, char *s2, bool to_free)
{
	size_t		i;
	char		*str;

	i = 0;
	str = alloc_join(s1, s2);
	if (str == NULL)
		return (NULL);
	while (s1[i])
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
	if (to_free)
		free(s1);
	str[i] = '\0';
	return (str);
}

size_t	ft_strlen_c(const char *str, char c, bool *found)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != c && str[i])
		i++;
	if (str[i] == c)
		*(found) = true;
	return (i);
}

void	*ft_memset2(void *s, int c, size_t n)
{
	char	*ptr;

	ptr = (char *)s;
	while (n--)
	{
		*ptr = (char)c;
		ptr++;
	}
	return (s);
}

int	ft_strcmp(const char *first, const char *second)
{
	size_t	i;

	i = 0;
	while (first[i] && second[i] && (first[i] == second[i]))
		i++;
	return ((unsigned char)first[i] - (unsigned char)second[i]);
}
