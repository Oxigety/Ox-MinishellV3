/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:19:02 by marvin            #+#    #+#             */
/*   Updated: 2024/04/14 14:19:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_export(t_shell *shell)
{
	t_env_list	*new_var;

	new_var = shell->list;
	while (new_var != NULL)
	{
		printf("export %s", new_var->var_name);
		if (new_var->value)
			printf("=\"%s\"\n", new_var->value);
		else
			printf("\n");
		new_var = new_var->next;
	}
}

void	change_var_value(t_shell *shell, int i, int j, char **v_cmd)
{
	t_env_list	*head;
	char		*target;
	char		*dup;

	if (ft_strchr(v_cmd[j], '=') == NULL)
		return ;
	head = shell->list;
	target = get_var_name(v_cmd[j]);
	if (!target)
		safe_exit(shell, NULL, NONE, 1);
	while (ft_strcmp(head->var_name, target) != 0)
		head = head->next;
	free(target);
	if (head->value != NULL)
		free(head->value);
	head->value = get_var_value(v_cmd[j]);
	if (!head->value)
		safe_exit(shell, NULL, NONE, 2);
	dup = ft_strdup(v_cmd[j]);
	if (!dup)
		safe_exit(shell, NULL, NONE, 2);
	free(shell->env[i]);
	shell->env[i] = dup;
}

void	add_to_export(t_shell *shell, char *new_var, char **v_cmd, int j)
{
	t_env_list	*new_list_node;
	char		**new_env;
	int			i;

	i = -1;
	if (!var_already_exists(shell, &i, new_var))
	{
		new_env = rewrite_env(shell, new_var, i);
		free(shell->env);
		shell->env = new_env;
		add_envlist(&shell, &new_list_node, new_var, false);
	}
	else
		change_var_value(shell, i, j, v_cmd);
}

void	add_null_env(t_shell *shell, char *new_var)
{
	t_env_list	*new_list_node;
	char		**new_env;
	char		*dup;

	dup = ft_strdup(new_var);
	if (!dup)
		safe_exit(shell, NULL, NONE, 1);
	new_env = malloc(sizeof(char *) * 2);
	if (!new_env)
		safe_exit(shell, NULL, NONE, 1);
	new_env[0] = dup;
	new_env[1] = NULL;
	ft_free(shell->env);
	shell->env = new_env;
	add_envlist(&shell, &new_list_node, new_var, true);
}

void	ft_export(t_shell *shell, char **v_cmd)
{
	int	i;

	i = 1;
	if (v_cmd[1] == NULL)
		return (print_export(shell));
	while (v_cmd[i] != NULL)
	{
		if (var_is_valid(v_cmd[i]))
		{
			if (shell->env[0] == NULL)
				add_null_env(shell, v_cmd[i]);
			else
				add_to_export(shell, v_cmd[i], v_cmd, i);
		}
		else
		{
			printferr(" not a valid identifier\n");
			shell->exitcode = 1;
		}
		i++;
	}
}
