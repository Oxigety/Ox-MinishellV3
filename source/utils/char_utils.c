/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Oxigety_ <Oxigety_@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:36:19 by Oxigety_          #+#    #+#             */
/*   Updated: 2024/07/22 13:36:20 by Oxigety_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_there_chr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c && !is_in_quotes(str, i))
			return (true);
		i++;
	}
	return (false);
}

bool	char_sym(const char s, const char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i++] == s)
			return (1);
	}
	return (0);
}

int	is_in_quotes(const char *str, int j)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (i <= j)
	{
		if ((str[i] == '"' && quotes == 0) || (str[i] == '\'' && quotes < 0))
			quotes++;
		else if ((str[i] == '\'' && quotes == 0) || (str[i] == '"'
				&& quotes > 0))
			quotes--;
		i++;
	}
	if (quotes < 0)
		return (1);
	if (quotes > 0)
		return (2);
	return (0);
}

char	*ft_strdup_c(const char *s, int *j, char c, bool *found)
{
	size_t	len;
	char	*str;
	int		i;

	len = ft_strlen_c(s, c, found);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] != c && s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	*j = ++i;
	return (str);
}

int	ft_strcmp_c(const char *first, const char *second, char c)
{
	size_t	i;

	i = 0;
	while (first[i] && second[i] && (first[i] == second[i])
		&& second[i] != c && first[i] != c)
		i++;
	if ((second[i] == '=' && !first[i]) || (first[i] == '=' && !second[i]))
		return (0);
	return ((unsigned char)first[i] - (unsigned char)second[i]);
}
