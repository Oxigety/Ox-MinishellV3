/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Oxigety_ <Oxigety_@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:41:50 by Oxigety_          #+#    #+#             */
/*   Updated: 2024/07/16 13:41:51 by Oxigety_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*redirection(t_command *cmd, char input_token, int i)
{
	char	*str;
	int		start;

	if (!is_there_chr(cmd->cmd, input_token))
		return (NULL);
	str = malloc(sizeof(char)
			* (last_redirection_size(cmd->cmd, input_token, &start) + 1));
	if (!str)
	{
		perror("minishell: malloc: ");
		return (NULL);
	}
	while (cmd->cmd[start])
	{
		if (ft_isspace(cmd->cmd[start]) && !is_in_quotes(cmd->cmd, start))
			break ;
		str[i++] = cmd->cmd[start++];
	}
	str[i] = '\0';
	if (is_there_chr(str, '"') || is_there_chr(str, '\''))
		str = str_without_quotes(str);
	return (str);
}

void	exec_redirections(t_shell *shell, t_command *cmd, int i)
{
	if (!is_there_chr(cmd->cmd, '>') && !is_there_chr(cmd->cmd, '<'))
		return ;
	cmd->input_redirection = redirection(cmd, '<', 0);
	cmd->output_redirection = redirection(cmd, '>', 0);
	while (cmd->cmd[i])
	{
		if (cmd->cmd[i] == '>' && !is_in_quotes(cmd->cmd, i))
			in_out_redirection(shell, cmd, STDOUT_FILENO, i++);
		if (cmd->cmd[i] == '<' && !is_in_quotes(cmd->cmd, i))
			in_out_redirection(shell, cmd, STDIN_FILENO, i++);
		i++;
	}
}
