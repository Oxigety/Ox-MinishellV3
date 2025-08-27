/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:24:19 by marvin            #+#    #+#             */
/*   Updated: 2024/04/12 15:24:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_getenv(t_shell *shell, char *target, char *to_free)
{
	t_env_list	*head;
	char		*res;

	res = NULL;
	head = shell->list;
	if (!target[0])
		return (res);
	while (head != NULL)
	{
		if (ft_strcmp(target, head->var_name) == 0)
		{
			if (head->value)
				res = ft_strdup(head->value);
			else
				res = ft_strdup("\0");
			if (!res)
				safe_exit(shell, to_free, STR, 2);
			break ;
		}
		else
			head = head->next;
	}
	return (res);
}

bool	contains_global_var(char *str, int *begin, int *end, int i)
{
	while (str[i])
	{
		if (str[i] == '$' && is_in_quotes(str, i) != 1)
		{
			if (is_heredoc_delim(str, &i, true))
				continue ;
			*begin = i;
			i++;
			if (str[i] == '?' || str[i] == ' ')
			{
				i++;
				*end = i - 1;
				return (true);
			}
			while (str[i] && ((str[i] >= 'A' && str[i] <= 'Z')
					|| (str[i] >= 'a' && str[i] <= 'z')
					|| (str[i] >= '0' && str[i] <= '9') || str[i] == '_'))
				i++;
			*end = i - 1;
			return (true);
		}
		i++;
	}
	return (false);
}

bool	valid_echo_opt(char *opt)
{
	int		i;
	bool	found;

	i = 0;
	found = false;
	if (opt[i++] == '-')
	{
		while (opt[i])
		{
			if (opt[i] != 'n')
				return (false);
			else
				found = true;
			i++;
		}
		if (found)
			return (true);
		else
			return (false);
	}
	return (false);
}

void	handle_echo_opt(char **v_cmd, int i, bool *is_opt, bool *no_newline)
{
	if (*(is_opt) && valid_echo_opt(v_cmd[i]))
		*(no_newline) = true;
	else
	{
		*(is_opt) = false;
		if (v_cmd[i + 1] == NULL)
			printf("%s", v_cmd[i]);
		else
			printf("%s ", v_cmd[i]);
	}
}

void	ft_echo(t_shell *shell, char **v_cmd)
{
	int		i;
	bool	no_newline;
	bool	is_opt;

	i = 1;
	is_opt = true;
	no_newline = false;
	if (v_cmd[1] == NULL)
	{
		printf("\n");
		shell->exitcode = 0;
		return ;
	}
	while (v_cmd[i] != NULL)
		handle_echo_opt(v_cmd, i++, &is_opt, &no_newline);
	if (!no_newline)
		printf("\n");
	shell->exitcode = 0;
}
