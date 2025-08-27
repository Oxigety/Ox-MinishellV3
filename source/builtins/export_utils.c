/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Oxigety_ <Oxigety_@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:21:27 by Oxigety_          #+#    #+#             */
/*   Updated: 2024/08/01 12:21:27 by Oxigety_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**rewrite_env(t_shell *shell, char *new_var, int i)
{
	char		**new_env;
	char		*dup;
	int			k;

	k = 0;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		safe_exit(shell, NULL, NONE, 1);
	dup = ft_strdup(new_var);
	if (!dup)
	{
		free(new_env);
		safe_exit(shell, NULL, NONE, 2);
	}
	while (k < i)
	{
		new_env[k] = shell->env[k];
		k++;
	}
	new_env[i] = dup;
	new_env[i + 1] = NULL;
	return (new_env);
}

int	var_already_exists(t_shell *shell, int *i, char *new)
{
	while (shell->env && shell->env[++(*i)])
	{
		if (ft_strcmp_c(shell->env[*i], new, '=') == 0)
			return (1);
	}
	return (0);
}
