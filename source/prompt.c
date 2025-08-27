/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babou <babou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:51:23 by bchapuis          #+#    #+#             */
/*   Updated: 2024/06/10 11:35:28 by babou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*path_string(t_shell *shell)
{
	char	*path;
	char	*path_end;
	char	*pwd;
	char	*colored_prompt;

	pwd = ft_get_cwd(shell);
	colored_prompt = "\001\033[1;34m\002minishell(\001\033[1;31m\002";
	if (!pwd)
		path = ft_strdup(colored_prompt);
	else
	{
		path = ft_strjoin_f(colored_prompt, pwd, false);
		ft_free(pwd);
	}
	if (!path)
		safe_exit(shell, NULL, NONE, 2);
	path_end = ft_strjoin_f(path, "\001\033[1;34m\002)> \001\033[0m\002",
			false);
	if (!path_end)
		safe_exit(shell, path, STR, 2);
	free(path);
	return (path_end);
}

bool	quotes_closed(const char *input)
{
	bool	single_quote_open;
	bool	double_quote_open;

	single_quote_open = false;
	double_quote_open = false;
	while (*input)
	{
		if (*input == '\'' && !double_quote_open)
			single_quote_open = !single_quote_open;
		else if (*input == '"' && !single_quote_open)
			double_quote_open = !double_quote_open;
		input++;
	}
	return (!single_quote_open && !double_quote_open);
}

bool	valid_quotes(t_shell *shell, char *input)
{
	if (!quotes_closed(input))
	{
		printferr("Error: Unclosed quotes\n");
		free_heredocs(shell->hdoc_list, true);
		free(shell->heredoc_name);
		free(input);
		return (false);
	}
	return (true);
}

char	*ft_read_input(t_shell *shell)
{
	char	*path;
	char	*str;

	path = path_string(shell);
	str = readline(path);
	free(path);
	if (str != NULL && str[0])
		add_history(str);
	if (str == NULL)
		return (NULL);
	if (handle_isspace(str))
		return (ft_strdup("\0"));
	shell->input = ft_strdup(str);
	if (!shell->input)
		return (ft_strdup("\0"));
	free(str);
	shell->input = search_heredoc(shell, shell->input, 0, NULL);
	if (!shell->input || !valid_quotes(shell, shell->input))
		return (ft_strdup("\0"));
	shell->input = expand_input(shell, shell->input);
	return (shell->input);
}
