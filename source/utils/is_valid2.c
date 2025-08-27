/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Oxigety_ <Oxigety_@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:49:49 by Oxigety_          #+#    #+#             */
/*   Updated: 2024/08/26 15:49:50 by Oxigety_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_command_valid(t_shell *shell, const char *message)
{
	if (is_starting_by_pipe(message) || is_ended_by_pipe(message)
		|| is_empty_pipe(message))
	{
		printferr("minishell: syntax error near unexpected token `|'\n");
		shell->exitcode = 2;
		return (false);
	}
	if ((!is_redirection_valid(message)))
	{
		printferr("minishell: syntax error near unexpected token ");
		find_invalid_syntax(message);
		printferr("\n");
		shell->exitcode = 2;
		return (false);
	}
	return (true);
}

void	print_redir_err(const char *str, int i)
{
	if (str[i] == '<')
	{
		if (str[i] && str[i + 1] == '<')
			printferr("'<<'");
		else if (str[i] && str[i + 1] == '>')
			printferr("'newline'");
	}
	else if (str[i] == '>')
	{
		if (str[i] && str[i + 1] == '>')
			printferr("'>>'");
		else if (str[i] && str[i + 1] == '<')
			printferr("'<'");
	}
}
