/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:22:59 by marvin            #+#    #+#             */
/*   Updated: 2024/04/12 15:22:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	updating_var(t_shell *shell, char *var, char *new_value)
{
	int	j;
	int	i;

	j = 0;
	i = -1;
	while (var[j])
		j++;
	while (shell->env[++i])
	{
		if (ft_strncmp(shell->env[i], var, j) == 0)
		{
			free(shell->env[i]);
			var = ft_strjoin_f(var, "=", false);
			if (!var)
				return (false);
			shell->env[i] = ft_strjoin_f(var, new_value, true);
			if (!shell->env[i])
			{
				free(var);
				return (false);
			}
			break ;
		}
	}
	return (true);
}

void	update_env_var(t_shell *shell, char *var, char *new_value)
{
	t_env_list	*head;
	bool		found;

	found = false;
	head = shell->list;
	while (head != NULL)
	{
		if (!ft_strcmp(head->var_name, var))
		{
			if (head->value)
				free(head->value);
			head->value = ft_strdup(new_value);
			if (!head->value)
				safe_exit(shell, NULL, NONE, 2);
			found = true;
			break ;
		}
		head = head->next;
	}
	if (found)
		if (!updating_var(shell, var, new_value))
			safe_exit(shell, head, NODE, 2);
}

int	get_newpwd(t_shell *shell, char *oldpwd, int err)
{
	char		*newpwd;

	newpwd = getcwd(NULL, 0);
	if (err || oldpwd == NULL || newpwd == NULL)
	{
		if (err && err < 5)
			perror("cd failed");
		ft_free(oldpwd);
		ft_free(newpwd);
		if (err == 0)
			err = 1;
		shell->exitcode = err;
		return (1);
	}
	update_env_var(shell, "OLDPWD", oldpwd);
	update_env_var(shell, "PWD", newpwd);
	ft_free(newpwd);
	return (0);
}

void	ft_cd(t_shell *shell, char **v_cmd)
{
	char		*oldpwd;
	int			err;

	err = 0;
	if (v_cmd[1] && v_cmd[2])
	{
		shell->exitcode = 1;
		return (printferr(" too many arguments\n"));
	}
	oldpwd = getcwd(NULL, 0);
	if (v_cmd[1] == NULL)
		goto_home_path(shell, &err);
	else if (v_cmd[1][0] == '~')
		goto_root_dir(shell, v_cmd[1], &err, true);
	else
	{
		if (chdir(v_cmd[1]) != 0)
			err += 1;
	}
	if (get_newpwd(shell, oldpwd, err))
		return ;
	free(oldpwd);
	shell->exitcode = 0;
}
