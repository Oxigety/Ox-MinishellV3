/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Oxigety_ <Oxigety_@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:52:20 by Oxigety_          #+#    #+#             */
/*   Updated: 2024/07/24 12:52:21 by Oxigety_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*extract_var_name(char **dollar_ptr)
{
	char	*end;
	char	*var_name;

	end = *dollar_ptr;
	while (*end && (ft_isalnum(*end) || *end == '_'))
		end++;
	var_name = ft_strndup(*dollar_ptr, end - *dollar_ptr);
	*dollar_ptr = end;
	return (var_name);
}

static char	*join_part(char *start, char *end, char *result)
{
	char	*before;
	char	*temp;

	before = ft_strndup(start, end - start);
	temp = ft_strjoin(result, before);
	if (!temp)
		return (NULL);
	free(result);
	free(before);
	return (temp);
}

char	*expand_single_variable(t_shell *shell, char **start,
char *dollar, char *result)
{
	char	*temp;
	char	*var_name;
	char	*var_value;

	result = join_part(*start, dollar, result);
	if (!result)
		return (NULL);
	dollar++;
	var_name = extract_var_name(&dollar);
	var_value = get_env_value(shell, var_name, NULL);
	temp = ft_strjoin(result, var_value);
	if (!temp)
	{
		free(result);
		free(var_name);
		return (NULL);
	}
	free(result);
	free(var_name);
	*start = dollar;
	return (temp);
}

void	init_list_fail(t_shell *shell, t_heredoc *new_heredoc,
		char *s1, char *s2)
{
	free(s1);
	free(s2);
	free(new_heredoc->delim);
	free(new_heredoc->filename);
	free(new_heredoc);
	safe_exit(shell, NULL, NONE, 2);
}

void	init_list_heredoc(char *delimiter, t_shell *shell,
		char *t_free, int lvl)
{
	t_heredoc	*new_heredoc;

	if (lvl < 0)
		return ;
	new_heredoc = malloc(sizeof(t_heredoc));
	if (!new_heredoc)
	{
		free(delimiter);
		free(t_free);
		safe_exit(shell, NULL, NONE, 2);
	}
	new_heredoc->delim = ft_strdup(delimiter);
	new_heredoc->filename = ft_strdup(shell->heredoc_name);
	new_heredoc->pipe_pos = lvl;
	if (!new_heredoc->delim || !new_heredoc->filename)
		init_list_fail(shell, new_heredoc, t_free, delimiter);
	new_heredoc->next = shell->hdoc_list;
	shell->hdoc_list = new_heredoc;
}
