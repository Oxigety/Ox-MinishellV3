/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Oxigety_ <Oxigety_@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:58:50 by Oxigety_          #+#    #+#             */
/*   Updated: 2024/07/18 17:58:51 by Oxigety_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(t_shell *shell, char *var_name, bool *found)
{
	t_env_list	*current;

	current = shell->list;
	while (current != NULL)
	{
		if (ft_strcmp(current->var_name, var_name) == 0)
		{
			if (current->value)
			{
				return (current->value);
			}
			else
				return ("");
		}
		current = current->next;
	}
	if (found)
		*found = false;
	return ("");
}

bool	check_if_open(char **input, char quote, bool *var, bool *truth)
{
	if (**input == quote && !(*var))
	{
		*truth = !(*truth);
		(*input) += 1;
		return (true);
	}
	return (false);
}

char	*handle_quotes_doll(t_shell *shell, char *input, char *res_ptr)
{
	char	*var_start;
	char	*var_name;
	char	*var_value;

	var_start = input + 1;
	while (ft_isalnum(*var_start) || *var_start == '_')
		var_start++;
	var_name = ft_strndup(input + 1, var_start - (input + 1));
	var_value = get_env_value(shell, var_name, NULL);
	free(var_name);
	if (var_value)
	{
		ft_strcpy(res_ptr, var_value);
		res_ptr += ft_strlen(var_value);
	}
	input = var_start;
	return (input);
}

char	*search_heredoc(t_shell *shell, char *input,
		size_t i, char *delimiter)
{
	char	*heredoc_pos;

	while (input && input[i])
	{
		heredoc_pos = ft_strnstr_i(input, "<<", ft_strlen(input), &i);
		if (!is_in_quotes(input, i) && heredoc_pos)
		{
			heredoc_pos += 2;
			delimiter = extract_delimiter(shell, heredoc_pos, 0);
			if (!delimiter)
				break ;
			if (handle_heredoc(shell, delimiter, input) == 0)
			{
				free(delimiter);
				free(input);
				return (NULL);
			}
			free(delimiter);
			i++;
		}
		else
			break ;
	}
	return (input);
}

char	*handle_quotes(t_shell *shell, char *input, bool s_is_open,
	bool d_is_open)
{
	char	*result;
	char	*res_ptr;
	char	*to_free;

	result = malloc(ft_strlen(input) + 1);
	if (!result)
		safe_exit(shell, input, STR, 2);
	res_ptr = result;
	to_free = input;
	while (*input)
	{
		if (check_if_open(&input, '\'', &d_is_open, &s_is_open)
			|| check_if_open(&input, '\"', &s_is_open, &d_is_open))
			continue ;
		*res_ptr++ = *input++;
	}
	*res_ptr = '\0';
	free(to_free);
	return (result);
}
