/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Oxigety_ <Oxigety_@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:54:41 by Oxigety_          #+#    #+#             */
/*   Updated: 2024/07/18 15:54:42 by Oxigety_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_empty_pipe(const char *str)
{
	int		i;
	bool	empty;

	i = 0;
	empty = false;
	while (str[i] && empty == false)
	{
		while (str[i] && (str[i] != '|' || (str[i] == '|'
					&& is_in_quotes(str, i))))
			i++;
		if (!str[i])
			return (false);
		if (str[i + 1] == '|')
			return (true);
		i++;
		empty = true;
		while (str[i] && (str[i] != '|' || (str[i] == '|'
					&& is_in_quotes(str, i))))
		{
			if ((!ft_strchr("|<>", str[i]) && !ft_isspace(str[i])))
				empty = false;
			i++;
		}
	}
	return (empty);
}

bool	is_ended_by_pipe(const char *str)
{
	int		i;
	int		j;
	bool	pipe;

	i = 0;
	j = -1;
	pipe = true;
	while (str[i])
	{
		if (str[i] == '|' && !is_in_quotes(str, i))
			j = i + 1;
		i++;
	}
	while (j > -1 && str[j] && pipe == true)
	{
		if (!ft_isspace(str[j]))
			pipe = false;
		j++;
	}
	if (j == -1)
		pipe = false;
	return (pipe);
}

bool	is_starting_by_pipe(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '|')
	{
		if (str[i] != '|' && !ft_isspace(str[i]))
			return (false);
		i++;
	}
	if (!str[i])
		return (false);
	return (true);
}

bool	is_invalid_char_in_quote(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((ft_strchr("~`#&*()\\[]{};!", str[i]) && !is_in_quotes(str, i))
			|| (str[i] == '?' && !is_in_quotes(str, i)
				&& i > 0 && str[i - 1] != '$'))
			return (true);
		i++;
	}
	return (false);
}

void	find_invalid_syntax(const char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '<' && str[i] != '>')
		i++;
	if (str[i + 1] == '<' || str[i + 1] == '>')
		i++;
	i++;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (!str[i])
		printferr("`newline'");
	else if (str[i] == '|')
		printferr("`|'");
	else
		print_redir_err(str, i);
}
