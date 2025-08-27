/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:23:56 by marvin            #+#    #+#             */
/*   Updated: 2024/04/12 15:23:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_cwd(t_shell *shell)
{
	t_env_list	*head;
	char		*path;

	head = shell->list;
	while (head && head->next)
	{
		if (!ft_strcmp(head->var_name, "PWD") && head->value != NULL)
		{
			path = ft_strdup(head->value);
			return (path);
		}
		head = head->next;
	}
	path = getcwd(NULL, 0);
	return (path);
}

void	ft_pwd(t_shell *shell)
{
	char	*pwd;
	int		err;

	err = 0;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		shell->exitcode = 1;
		perror("pwd failed");
	}
	else
		printf("%s\n", pwd);
	if (pwd)
		free(pwd);
	shell->exitcode = err;
}
