/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchapuis <bchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:57:35 by bchapuis          #+#    #+#             */
/*   Updated: 2024/05/21 15:05:49 by bchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	convert_code(char *str, int *err, int sign, unsigned long long total)
{
	size_t				i;
	unsigned long long	max;

	i = 0;
	max = 9223372036854775807;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i++] == 45)
			sign *= -1;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		total = total * 10 + (str[i++] - 48);
		if ((total > max + 1 && sign < 0) || (total > LLONG_MAX
				&& sign > 0))
		{
			*err = 2;
			return (2);
		}
	}
	*err += check_invalid_char(str + i);
	return (total * sign);
}

int	correct_exit_code(int input)
{
	int	code;

	code = input;
	while (code > 255)
	{
		code = code - 256;
	}
	while (code < 0)
	{
		code = code + 256;
	}
	return (code);
}

int	get_exit_code(char *str)
{
	int		code;
	int		err;

	err = 0;
	code = convert_code(str, &err, 1, 0);
	if (code > 255 || code < 0)
		code = correct_exit_code(code);
	if (err > 1)
	{
		printferr(" numeric argument required\n");
		code = 2;
	}
	else
		printf("exit\n");
	return (code);
}

int	del_envlist(t_shell **shell, char *name)
{
	t_env_list	*var;
	t_env_list	*new;

	var = (*shell)->list;
	if (ft_strcmp(name, var->var_name) == 0)
	{
		(*shell)->list = var->next;
		free(var->var_name);
		free(var->value);
		free(var);
		return (0);
	}
	while (ft_strcmp(name, var->next->var_name) != 0)
	{
		var = var->next;
		if (var->next == NULL)
			return (1);
	}
	new = var->next->next;
	free(var->next->var_name);
	free(var->next->value);
	free(var->next);
	var->next = new;
	return (0);
}

int	ft_is_exit(t_shell *shell, char **v_cmd)
{
	if (v_cmd[1] && v_cmd[2])
	{
		shell->exitcode = get_exit_code(v_cmd[1]);
		if (shell->exitcode == 2)
			return (1);
		printferr(" too many arguments\n");
		shell->exitcode = 1;
		return (0);
	}
	if (v_cmd[1])
		shell->exitcode = get_exit_code(v_cmd[1]);
	else
	{
		printf("exit\n");
		shell->exitcode = 0;
	}
	return (1);
}
