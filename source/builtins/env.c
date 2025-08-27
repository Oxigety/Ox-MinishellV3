/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:24:59 by marvin            #+#    #+#             */
/*   Updated: 2024/04/12 15:24:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_shell *shell)
{
	t_env_list	*head;
	int			i;

	i = 0;
	head = shell->list;
	if (head == NULL)
	{
		shell->exitcode = 125;
		return ;
	}
	while (head != NULL)
	{
		if (head->value)
			printf("%s=%s\n", head->var_name, head->value);
		head = head->next;
		i++;
	}
	shell->exitcode = 0;
}

void	init_envp(t_shell *shell, char **envp)
{
	t_env_list	*new_var;
	size_t		len;
	size_t		i;

	len = 0;
	i = 0;
	while (envp[len])
		len++;
	shell->env = malloc((len + 1) * sizeof(char *));
	if (!shell->env)
		safe_exit(shell, NULL, NONE, 2);
	if (env_is_empty(shell, len))
		return ;
	while (i < len && len != 0)
	{
		shell->env[i] = ft_strdup(envp[i]);
		if (!shell->env[i])
			safe_exit(shell, NULL, NONE, 2);
		i++;
	}
	shell->env[len] = NULL;
	i = 0;
	add_envlist(&shell, &new_var, envp[0], true);
	while (++i < len)
		add_envlist(&shell, &new_var, envp[i], false);
}
