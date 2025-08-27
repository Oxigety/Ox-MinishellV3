/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Oxigety_ <Oxigety_@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:55:39 by Oxigety_          #+#    #+#             */
/*   Updated: 2024/07/23 14:55:39 by Oxigety_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean_child_exit(t_shell *shell, char *t_free)
{
	ft_free_split(shell->env);
	ft_free_env(&shell->list);
	ft_free(t_free);
	ft_free(shell->heredoc_delim);
	free_heredocs(shell->hdoc_list, false);
	close(shell->stdin);
	if (shell->heredoc_name)
		free(shell->heredoc_name);
	exit(0);
}

void	heredoc_fork(t_shell *shell, char *delimiter, char *t_free)
{
	char	*line;
	char	*content;

	line = NULL;
	content = ft_strdup("");
	shell->heredoc_delim = delimiter;
	free_shell_addr(shell, t_free, content, false);
	if (!content)
	{
		free(t_free);
		safe_exit(shell, delimiter, STR, 2);
	}
	while (42)
	{
		if (can_i_leave_please(&line, delimiter))
			break ;
		content = is_expand_needed(shell, line, t_free, content);
		if (!content)
			safe_exit(shell, delimiter, STR, 2);
		free_shell_addr(shell, t_free, content, false);
	}
	open_and_write_child(shell, content, "fork_content.tmp", delimiter);
	clean_child_exit(shell, t_free);
}

void	open_and_write_child(t_shell *shell, char *content, char *name,
		char *delim)
{
	ssize_t	written;
	int		fd;

	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(delim);
		free(shell->input);
		free(content);
		error(shell, 1);
	}
	if (content)
	{
		written = write(fd, content, ft_strlen(content));
		if (written < 0)
			perror("write");
		free(content);
	}
	close(fd);
}

void	open_and_write_heredoc(t_shell *shell, char *content, char *delim)
{
	ssize_t	written;
	int		fd;

	fd = open(shell->heredoc_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(delim);
		free(shell->input);
		free(content);
		error(shell, 1);
	}
	if (content)
	{
		written = write(fd, content, ft_strlen(content));
		if (written < 0)
			perror("write");
		free(content);
	}
	close(fd);
}

char	*extract_delimiter(t_shell *shell, char *heredoc_pos, size_t length)
{
	char	*delimiter;

	if (!*heredoc_pos)
		return (NULL);
	while (ft_isspace(*heredoc_pos))
		heredoc_pos++;
	find_delim_quote_char(shell, &heredoc_pos);
	length = get_del_length(heredoc_pos);
	if (length == 0)
		return (NULL);
	delimiter = malloc(length + 1);
	if (!delimiter)
		return (NULL);
	ft_strlcpy(delimiter, heredoc_pos, length + 1);
	delimiter = str_without_quotes(delimiter);
	return (delimiter);
}
