/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Oxigety_ <Oxigety_@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:15:14 by Oxigety_          #+#    #+#             */
/*   Updated: 2024/07/19 11:15:15 by Oxigety_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env_list	*create_new_env_node(void)
{
	t_env_list	*new_node;

	new_node = malloc(sizeof(t_env_list));
	if (!(new_node))
		return (NULL);
	new_node->next = NULL;
	new_node->value = NULL;
	new_node->var_name = NULL;
	return (new_node);
}

void	new_to_list(t_shell **shell, t_env_list **new_node, char *var, int j)
{
	bool		found;
	t_env_list	*head;

	found = false;
	(*new_node) = create_new_env_node();
	if (!(*new_node))
		safe_exit(*shell, NULL, NONE, 1);
	(*new_node)->var_name = ft_strdup_c(var, &j, '=', &found);
	if (!(*new_node)->var_name)
		safe_exit(*shell, (*new_node), NODE, 1);
	var += j;
	if (found == false)
		(*new_node)->value = NULL;
	else
		(*new_node)->value = ft_strdup_c(var, &j, '\0', &found);
	if ((!(*new_node)->value) && found == true)
		safe_exit(*shell, (*new_node), NODE, 1);
	head = (*shell)->list;
	while (head->next)
		head = head->next;
	head->next = *new_node;
	(*new_node)->next = NULL;
}

void	add_envlist(t_shell **shell, t_env_list **new_node,
	char *var, bool lone)
{
	int			j;
	bool		found;

	j = 0;
	found = false;
	if (lone == false)
		new_to_list(shell, new_node, var, 0);
	else
	{
		(*shell)->list = create_new_env_node();
		if (!((*shell)->list))
			safe_exit(*shell, NULL, NONE, 1);
		(*shell)->list->var_name = ft_strdup_c(var, &j, '=', &found);
		if (!(*shell)->list->var_name)
			safe_exit(*shell, NULL, NONE, 1);
		var += j;
		if (found == false)
			(*shell)->list->value = NULL;
		else
		{
			(*shell)->list->value = ft_strdup_c(var, &j, '\0', &found);
			if (!(*shell)->list->value)
				safe_exit(*shell, NULL, NONE, 1);
		}
	}
}

void	add_basic_paths(t_shell *shell)
{
	t_env_list	*new_var;
	char		**simple_env;
	char		user[50];

	simple_env = malloc(4 * sizeof(char *));
	if (!simple_env)
		safe_exit(shell, NULL, NONE, 2);
	simple_env[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
	simple_env[1] = ft_strdup("OLDPWD");
	getlogin_r(user, 50);
	simple_env[2] = ft_strjoin("USER=", user);
	if (!simple_env[0] || !simple_env[1] || !simple_env[2])
	{
		ft_free(simple_env[2]);
		ft_free(simple_env[1]);
		safe_exit(shell, simple_env[0], STR, 2);
	}
	simple_env[3] = NULL;
	shell->env = simple_env;
	add_envlist(&shell, &new_var, simple_env[0], true);
	add_envlist(&shell, &new_var, simple_env[1], false);
	add_envlist(&shell, &new_var, simple_env[2], false);
}

bool	env_is_empty(t_shell *shell, int len)
{
	if (len == 0)
	{
		add_basic_paths(shell);
		return (true);
	}
	return (false);
}
