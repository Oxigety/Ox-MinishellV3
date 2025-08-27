/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Oxigety_ <Oxigety_@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:20:44 by Oxigety_          #+#    #+#             */
/*   Updated: 2024/07/22 13:20:45 by Oxigety_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strndup(const char *s, int n)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * n + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strcpy(char *dest, const char *src)
{
	char	*start;

	start = dest;
	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (start);
}

char	*ft_strnstr_i(const char *big, const char *little,
size_t len, size_t *i)
{
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	while (big[*i] && *i < len)
	{
		j = 0;
		while (big[*i + j] == little[j] && *i + j < len && little[j])
		{
			if (little[j + 1] == '\0')
				return ((char *)&big[*i]);
			j++;
		}
		(*i)++;
	}
	return (NULL);
}

char	*ft_strdup2(const char *s)
{
	size_t	len;
	char	*str;
	int		i;

	if (s[0] == '\0')
	{
		str = malloc(sizeof(char));
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	len = ft_strlen(s);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
