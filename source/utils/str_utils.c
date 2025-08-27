/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Oxigety_ <Oxigety_@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:42:09 by Oxigety_          #+#    #+#             */
/*   Updated: 2024/07/22 13:42:09 by Oxigety_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_heredoc_delim(char *str, int *i, bool incr)
{
	int	j;

	j = *i - 1;
	while (j >= 0)
	{
		while (j >= 0 && is_in_quotes(str, j))
			j--;
		if (j >= 0 && (str[j] == '\'' || str[j] == '\"'))
			j--;
		while (j >= 0 && ft_isspace(str[j]))
			j--;
		if (j >= 1 && str[j] == '<' && str[j - 1] == '<')
		{
			if (incr)
				(*i)++;
			return (true);
		}
		return (false);
	}
	return (false);
}

void	copy_without_redirections(char *cmd, char *result)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if ((cmd[i] == '>' || cmd[i] == '<') && !is_in_quotes(cmd, i))
			size_redirection(cmd, &i, 0);
		if (!cmd[i])
			break ;
		result[j++] = cmd[i++];
	}
	result[j] = '\0';
}

char	*str_without_quotes(char *str)
{
	char			*result;

	result = malloc(sizeof(char) * (ft_strlen(str) - count_quotes(str) + 1));
	if (!result)
	{
		perror("minishell: malloc: ");
		free(str);
		return (NULL);
	}
	copy_quoteless(result, str);
	free(str);
	return (result);
}

void	copy_quoteless(char *result, char *str)
{
	unsigned int	i;
	unsigned int	j;
	int				qts;

	i = 0;
	j = 0;
	qts = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && qts == 0)
		{
			qts++;
			if (str[i] == '\'')
				qts -= 2;
		}
		else if ((str[i] == '\'' && qts == -1) || (str[i] == '"' && qts == 1))
			qts = 0;
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
}

void	copy_without_quotes(char *word, const char *s, unsigned int start,
							unsigned int end)
{
	int				quotes;
	unsigned int	i;

	i = 0;
	quotes = 0;
	while (start <= end)
	{
		if ((s[start] == '\'' || s[start] == '"') && quotes == 0)
		{
			if (s[start] == '\'')
				quotes--;
			else
				quotes++;
		}
		else if (((s[start] == '\'' && quotes == -1)
				|| (s[start] == '"' && quotes == 1)))
			quotes = 0;
		else
			word[i++] = s[start];
		start++;
	}
	word[i - 1] = '\0';
}
