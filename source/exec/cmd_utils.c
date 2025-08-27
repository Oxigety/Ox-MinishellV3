/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Oxigety_ <Oxigety_@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:40:33 by Oxigety_          #+#    #+#             */
/*   Updated: 2024/07/22 13:40:34 by Oxigety_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	count_pipes(t_shell *shell, const char *str)
{
	size_t	count;
	int		i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '|' && !is_in_quotes(str, i))
			count++;
		i++;
	}
	shell->nb_pipes = count;
	return (count);
}

void	cmd_new(t_command *prev)
{
	t_command	*command;

	command = (t_command *)malloc(sizeof(t_command));
	if (!command)
		return ;
	ft_memset(command, 0, sizeof(t_command));
	prev->next = command;
	command->prev = prev;
}

bool	handle_command2(t_shell *shell, t_command *cmd)
{
	if (cmd->v_cmd[0] != NULL && ft_strlen(cmd->v_cmd[0]) > 0)
	{
		if (ft_strcmp(cmd->v_cmd[0], "exit") == 0 && shell->nb_pipes == 0)
			shell->exit = ft_is_exit(shell, cmd->v_cmd);
		else if (ft_strcmp(cmd->v_cmd[0], "cd") == 0 && shell->nb_pipes == 0)
			ft_cd(shell, cmd->v_cmd);
		else if (ft_strcmp(cmd->v_cmd[0], "unset") == 0 && shell->nb_pipes == 0)
			ft_unset(shell, cmd->v_cmd);
		else if (ft_strcmp(cmd->v_cmd[0], "export") == 0
			&& cmd->v_cmd[1] && shell->nb_pipes == 0)
			ft_export(shell, cmd->v_cmd);
		else
			return (false);
		return (true);
	}
	else
		return (false);
}
