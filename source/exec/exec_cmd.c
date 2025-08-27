/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Oxigety_ <Oxigety_@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:18:58 by Oxigety_          #+#    #+#             */
/*   Updated: 2024/07/16 15:18:59 by Oxigety_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	handle_command3(t_shell *shell, t_command *cmd)
{
	if (cmd->v_cmd[0] != NULL && ft_strlen(cmd->v_cmd[0]) > 0)
	{
		if (ft_strcmp(cmd->v_cmd[0], "exit") == 0)
			shell->exit = ft_is_exit(shell, cmd->v_cmd);
		else if (ft_strcmp(cmd->v_cmd[0], "cd") == 0)
			ft_cd(shell, cmd->v_cmd);
		else if (ft_strcmp(cmd->v_cmd[0], "pwd") == 0)
			ft_pwd(shell);
		else if (ft_strcmp(cmd->v_cmd[0], "echo") == 0)
			ft_echo(shell, cmd->v_cmd);
		else if (ft_strcmp(cmd->v_cmd[0], "env") == 0)
			ft_env(shell);
		else if (ft_strcmp(cmd->v_cmd[0], "unset") == 0)
			ft_unset(shell, cmd->v_cmd);
		else if (ft_strcmp(cmd->v_cmd[0], "export") == 0)
			ft_export(shell, cmd->v_cmd);
		else
			return (false);
		return (true);
	}
	else
		return (false);
}

char	**get_split_path(t_shell *shell, char **env)
{
	char	**path;
	int		i;

	i = -1;
	if (!(*env))
	{
		return (NULL);
	}
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			break ;
	}
	path = ft_split(env[i] + 5, ':');
	if (path == NULL)
		error(shell, 2);
	return (path);
}

int	final_exec_cmd(t_shell *shell, t_command *cmd,
		int i, int *pipes_fd)
{
	if (!(shell->path))
		shell->path = get_cmd_path(shell, cmd->v_cmd[0], shell->split_path, i);
	if (!shell->path)
	{
		ft_free_split(shell->split_path);
		safe_exit(shell, NULL, NONE, 2);
	}
	while (i < 2 * shell->nb_pipes)
		close(pipes_fd[i++]);
	close(shell->stdin);
	if (execve(shell->path, cmd->v_cmd, shell->env) == -1 && errno != 2)
	{
		ft_free_split(shell->split_path);
		shell->split_path = NULL;
		ft_free(shell->path);
		return (1);
	}
	free(shell->path);
	return (0);
}

int	exec(t_shell *shell, t_command *cmd, int *pipes_fd)
{
	int		i;

	i = 0;
	if (cmd->v_cmd[0] == NULL)
		return (0);
	if (handle_command3(shell, cmd))
	{
		while (i < 2 * shell->nb_pipes)
			close(pipes_fd[i++]);
		close(shell->stdin);
		return (0);
	}
	if (!path_is_real(shell, shell->env, cmd))
		return (1);
	shell->path = manage_path_type(shell, cmd->v_cmd[0]);
	shell->split_path = get_split_path(shell, shell->env);
	while (shell->split_path && shell->split_path[i])
	{
		if (final_exec_cmd(shell, cmd, i, pipes_fd))
			return (1);
		shell->path = NULL;
		i++;
	}
	return (1);
}
