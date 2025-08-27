/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Oxigety_ <Oxigety_@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:04:39 by Oxigety_          #+#    #+#             */
/*   Updated: 2024/07/18 17:04:40 by Oxigety_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	goto_home_path(t_shell *shell, int *err)
{
	t_env_list	*head;
	bool		found;

	head = shell->list;
	found = false;
	while (head != NULL)
	{
		if (!ft_strcmp(head->var_name, "HOME"))
		{
			found = true;
			if (chdir(head->value) != 0)
				*err += 1;
			return ;
		}
		head = head->next;
	}
	printf("cd: HOME not set\n");
	if (!found)
		*err += 5;
}

char	*get_tilde_path(t_shell *shell, char *cmd, bool *found,
	bool *free_needed)
{
	char	*path;

	path = NULL;
	if (ft_strcmp(cmd, "~-") == 0)
		path = get_env_value(shell, "OLDPWD", found);
	else if (ft_strcmp(cmd, "~+") == 0)
		path = get_env_value(shell, "PWD", found);
	else if (ft_strcmp(cmd, "~") == 0)
	{
		*free_needed = true;
		path = ft_strjoin("/home/", get_env_value(shell, "USER", found));
	}
	else
	{
		path = ft_strdup(cmd);
		*free_needed = true;
	}
	return (path);
}

void	goto_root_dir(t_shell *shell, char *cmd, int *err, bool found)
{
	bool		free_needed;
	char		*path;

	path = NULL;
	free_needed = false;
	path = get_tilde_path(shell, cmd, &found, &free_needed);
	if (!found)
		*err += 5;
	if (chdir(path) != 0)
		*err += 1;
	if (free_needed)
		free(path);
}
