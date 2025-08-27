/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:30:18 by marvin            #+#    #+#             */
/*   Updated: 2024/04/12 15:30:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*join_path_cmd(t_shell *shell, char *path, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(path, "/");
	if (tmp == NULL)
	{
		free(path);
		error(shell, 1);
	}
	full_path = ft_strjoin(tmp, cmd);
	if (full_path == NULL)
	{
		free(tmp);
		free(path);
		error(shell, 1);
	}
	free(tmp);
	return (full_path);
}

char	*add_abs_path(t_shell *shell, char *res, char *cmd)
{
	char	*abs_path;

	abs_path = getcwd(NULL, 0);
	if (!abs_path)
	{
		perror("Error path: ");
		return (NULL);
	}
	res = ft_strjoin(abs_path, cmd + 1);
	if (!res)
	{
		free(res);
		error(shell, 2);
	}
	free(abs_path);
	return (res);
}

char	*manage_path_type(t_shell *shell, char *cmd)
{
	char	*res;

	res = NULL;
	if (!cmd)
		return (NULL);
	if (cmd[0] == '/')
	{
		res = ft_strdup(cmd);
		if (!res)
			error(shell, 2);
		return (res);
	}
	if (ft_strncmp(cmd, "./", 2))
	{
		return (NULL);
	}
	res = add_abs_path(shell, res, cmd);
	return (res);
}

char	*get_cmd_path(t_shell *shell, char *cmd, char **path, int i)
{
	char	*full_path;

	if (!path)
		return (NULL);
	if (path[i])
	{
		full_path = join_path_cmd(shell, path[i], cmd);
		return (full_path);
	}
	return (NULL);
}
