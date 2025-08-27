/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Oxigety_ <Oxigety_@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:30:00 by Oxigety_          #+#    #+#             */
/*   Updated: 2024/08/26 15:30:00 by Oxigety_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*copy_file_into_content(t_shell *shell, char *tf1, char *tf2)
{
	char	*res;
	char	*line;
	int		fd;

	res = ft_strdup("");
	fd = open("fork_content.tmp", O_RDONLY);
	if (fd == -1)
	{
		free(tf1);
		free(tf2);
		safe_exit(shell, res, STR, 2);
	}
	else
	{
		while (42)
		{
			line = get_next_line(fd);
			if (!line)
				break ;
			res = ft_strjoin_f(res, line, true);
			free(line);
		}
		close(fd);
	}
	return (res);
}

t_shell	*free_shell_addr(t_shell *shell, char *s1, char *s2, bool to_free)
{
	static t_shell	*saved_shell;
	static char		*tf;
	static char		*content;

	if (!to_free)
	{
		saved_shell = shell;
		tf = s1;
		content = s2;
	}
	else
	{
		ft_free_split(saved_shell->env);
		ft_free_env(&saved_shell->list);
		ft_free(tf);
		ft_free(content);
		ft_free(saved_shell->heredoc_delim);
	}
	return (saved_shell);
}

bool	can_i_leave_please(char **line, char *delimiter)
{
	*line = readline("> ");
	if (!(*line))
	{
		printferr("minishell: warning: here-document");
		printferr(" delimited by end-of-file (wanted '");
		printferr(delimiter);
		printferr("')\n");
		return (true);
	}
	if (ft_strcmp(*line, delimiter) == 0)
	{
		free(*line);
		return (true);
	}
	return (false);
}
