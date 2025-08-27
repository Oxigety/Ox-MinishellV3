/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchapuis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 07:25:47 by bchapuis          #+#    #+#             */
/*   Updated: 2023/11/22 07:25:52 by bchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(const char *str, char c)
{
	size_t		nbr;

	nbr = 0;
	while (*str)
	{
		if (*str == c)
			str++;
		else
		{
			nbr++;
			while (*str && *str != c)
				str++;
		}
	}
	return (nbr);
}

static	void	ft_freesplit(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	strs = NULL;
}

static	char	**ft_fill(char const *s, char c, size_t len, char	**strs)
{
	size_t		i;
	size_t		j;

	i = 0;
	while (i < len)
	{
		while (*s == c)
			s++;
		j = 0;
		while (s[j] != c && s[j])
			j++;
		strs[i] = ft_substr(s, 0, j);
		s += j;
		if (!strs[i++])
		{
			ft_freesplit(strs);
			return (NULL);
		}
	}
	strs[i] = NULL;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char		**strs;
	size_t		len;

	if (!s)
		return (NULL);
	len = ft_count_words(s, c);
	strs = (char **) malloc(sizeof(char *) * (len + 1));
	if (!strs)
		return (NULL);
	strs = ft_fill(s, c, len, strs);
	return (strs);
}
