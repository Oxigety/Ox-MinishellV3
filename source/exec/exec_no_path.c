/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_no_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Oxigety_ <Oxigety_@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:24:31 by Oxigety_          #+#    #+#             */
/*   Updated: 2024/07/25 14:24:31 by Oxigety_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_cmd_no_path(t_shell *shell, t_command *cmd, char *path)
{
	int	i;

	i = 0;
	while (i < 2 * shell->nb_pipes)
		close(shell->pipe_fds[i++]);
	close(shell->stdin);
	if (execve(path, cmd->v_cmd, shell->env) == -1 && errno != 2)
	{
		ft_free(path);
		return (1);
	}
	free(path);
	return (0);
}

bool	ft_no_path(t_shell *shell, t_command *cmd)
{
	char	*path;

	path = manage_path_type(shell, cmd->v_cmd[0]);
	if (!path)
		path = ft_strdup(cmd->v_cmd[0]);
	if (!path)
		safe_exit(shell, NULL, NONE, 2);
	exec_cmd_no_path(shell, cmd, path);
	return (false);
}

bool	path_is_real(t_shell *shell, char **env, t_command *cmd)
{
	int		i;

	i = 0;
	if (*env == NULL)
		return (ft_no_path(shell, cmd));
	else
	{
		while (env[i])
		{
			if (!ft_strncmp(env[i], "PATH=", 5))
				return (true);
			i++;
		}
		return (ft_no_path(shell, cmd));
	}
	return (false);
}
