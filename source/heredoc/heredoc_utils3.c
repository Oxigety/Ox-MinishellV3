/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Oxigety_ <Oxigety_@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:19:02 by Oxigety_          #+#    #+#             */
/*   Updated: 2024/08/01 12:19:02 by Oxigety_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_del_length(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if ((ft_isspace(str[i]) || str[i] == '|' || str[i] == '<'
				|| str[i] == '>') && !is_in_quotes(str, i))
			break ;
		i++;
	}
	return (i);
}

void	find_delim_quote_char(t_shell *shell, char **str)
{
	if (**str == '\'' || **str == '"')
	{
		shell->heredoc_quoted = true;
	}
	else
		shell->heredoc_quoted = false;
}

char	*expand_variables(t_shell *shell, char *input, char *result)
{
	char		*start;
	char		*dollar;
	char		*temp;
	char		*remaining;

	start = input;
	if (!result)
		return (NULL);
	dollar = ft_strchr(start, '$');
	while (dollar != NULL)
	{
		temp = expand_single_variable(shell, &start, dollar, result);
		if (!temp)
		{
			free(result);
			return (NULL);
		}
		result = temp;
		dollar = ft_strchr(start, '$');
	}
	remaining = ft_strdup(start);
	temp = ft_strjoin(result, remaining);
	free(result);
	free(remaining);
	return (temp);
}

char	*is_expand_needed(t_shell *shell, char *line,
char *t_free, char *content)
{
	char	*expanded_line;

	if (!shell->heredoc_quoted)
	{
		expanded_line = expand_variables(shell, line, ft_strdup(""));
		if (!expanded_line)
		{
			free(t_free);
			free(content);
			return (NULL);
		}
		content = ft_strjoin_f(content, expanded_line, true);
		free(expanded_line);
	}
	else
		content = ft_strjoin_f(content, line, true);
	content = ft_strjoin_f(content, "\n", true);
	free(line);
	return (content);
}
