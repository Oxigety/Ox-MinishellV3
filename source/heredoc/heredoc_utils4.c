/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Oxigety_ <Oxigety_@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:03:34 by Oxigety_          #+#    #+#             */
/*   Updated: 2024/08/27 18:03:35 by Oxigety_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	reuse_tmp(t_heredoc *list, char *delim, int lvl)
{
	t_heredoc	*head;

	head = list;
	if (!list)
	{
		return (false);
	}
	while (head != NULL)
	{
		if (ft_strcmp(head->delim, delim) == 0 && lvl == head->pipe_pos)
		{
			return (true);
		}
		head = head->next;
	}
	return (false);
}

void	moove_into_next_redir(t_shell *shell, char *t_free, bool reset)
{
	t_heredoc		*head;
	static size_t	i = 0;
	static size_t	j = 0;

	if (reset)
	{
		i = 0;
		j = 0;
		return ;
	}
	head = shell->hdoc_list;
	ft_strnstr_i(t_free, "<<", ft_strlen(t_free), &(i));
	i++;
	while (j < i)
	{
		if (t_free[j] == '|' && !is_in_quotes(t_free, j))
		{
			shell->saved_index += 1;
		}
		j++;
	}
}

void	check_heredoc_existence(t_shell *shell, char *t_free, char *delim,
	char *content)
{
	char	*counter_str;

	moove_into_next_redir(shell, t_free, false);
	if (!reuse_tmp(shell->hdoc_list, delim, shell->saved_index))
	{
		counter_str = ft_itoa(shell->heredoc_counter++);
		if (shell->heredoc_name)
			free(shell->heredoc_name);
		shell->heredoc_name = ft_strjoin(".tmp_", counter_str);
		if (!shell->heredoc_name)
		{
			free(counter_str);
			safe_exit(shell, t_free, STR, 2);
		}
		free(counter_str);
		open_and_write_heredoc(shell, content, delim);
		init_list_heredoc(delim, shell, t_free, shell->saved_index);
		return ;
	}
	open_and_write_heredoc(shell, content, delim);
}
