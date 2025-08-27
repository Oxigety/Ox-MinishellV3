/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Oxigety_ <Oxigety_@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:34:25 by Oxigety_          #+#    #+#             */
/*   Updated: 2024/07/08 12:34:31 by Oxigety_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*cut_commands(const char *message, int letter, int j)
{
	static int	i = 0;
	char		*cmd;

	if (message[i] == '|')
		i++;
	j = i;
	while (message[i])
	{
		if (message[i] == '|' && !is_in_quotes(message, i))
			break ;
		i++;
	}
	cmd = malloc(sizeof(char) * (i - j + 1));
	if (!cmd)
		return (NULL);
	while (j < i)
		cmd[letter++] = message[j++];
	cmd[letter] = '\0';
	if (!message[i])
		i = 0;
	return (cmd);
}

bool	create_cmd_list(t_shell *shell)
{
	t_command	*command;
	int			i;

	i = 0;
	command = shell->cmd_list;
	while (i < shell->nb_pipes)
	{
		cmd_new(command);
		if (!command->next)
		{
			ft_free(shell->str);
			free_cmd_list(command);
			perror("minishell: malloc: ");
			return (false);
		}
		command = command->next;
		i++;
	}
	return (true);
}

bool	split_command(t_shell *shell, t_command *command)
{
	char	*cmd_clean;

	while (command)
	{
		cmd_clean = clean_command(command->cmd);
		if (!cmd_clean)
		{
			ft_free(shell->str);
			free_cmd_list(command);
			perror("minishell: malloc: ");
			return (false);
		}
		command->v_cmd = split_arguments(cmd_clean, " \n\r\t\v\f");
		if (!command->v_cmd)
		{
			ft_free(shell->str);
			ft_free(cmd_clean);
			free_cmd_list(command);
			perror("minishell: malloc: ");
			return (false);
		}
		command = command->next;
		ft_free(cmd_clean);
	}
	return (true);
}

bool	standardize_command(t_shell *shell, t_command *command)
{
	command = shell->cmd_list;
	if (!is_command_valid(shell, shell->str))
		return (false);
	if (count_pipes(shell, shell->str) > MAX_NB_PIPES)
	{
		printf("Too many fd ! Try opening less pipes.\n");
		return (false);
	}
	if (!create_cmd_list(shell))
		return (false);
	while (command)
	{
		command->cmd = cut_commands(shell->str, 0, 0);
		if (!command->cmd)
		{
			ft_free(shell->str);
			free_cmd_list(shell->cmd_list);
			perror("minishell: malloc: ");
			return (false);
		}
		command = command->next;
	}
	if (!split_command(shell, shell->cmd_list))
		return (false);
	return (true);
}

int	process_message(t_shell *shell)
{
	ft_memset2(shell->cmd_list, 0, sizeof(t_command));
	if (!standardize_command(shell, NULL))
	{
		free(shell->str);
		return (4);
	}
	return (0);
}
