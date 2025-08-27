/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 11:00:47 by marvin            #+#    #+#             */
/*   Updated: 2024/04/13 11:00:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error(t_shell *shell, int exit_code)
{
	perror("Error");
	safe_exit(shell, NULL, NONE, exit_code);
}

void	exec_errors(t_shell *shell, t_command *cmd)
{
	if (errno == EACCES && chdir(*cmd->v_cmd) == -1)
		print_errors(shell, 126, cmd->v_cmd[0],
			": Permission denied\n");
	else if (errno == EACCES)
		print_errors(shell, 126, cmd->v_cmd[0],
			": Is a directory\n");
	else if (**cmd->v_cmd == '/' || (**cmd->v_cmd == '.'
			&& **cmd->v_cmd + 1 == '/'))
		print_errors(shell, 127, cmd->v_cmd[0],
			": No such file or directory\n");
	else
		print_errors(shell, 128, cmd->v_cmd[0], ": command not found\n");
}

void	printferr(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
}

void	print_errors(t_shell *shell, int exit_code, char *s2, char *s3)
{
	char	*err_msg;
	char	*first_join;
	char	*s1;

	err_msg = NULL;
	s1 = "minishell: ";
	if (exit_code == 128 && exit_code--)
		s1 = "";
	shell->exitcode = exit_code;
	first_join = ft_strjoin_f(s1, s2, false);
	err_msg = ft_strjoin_f(first_join, s3, false);
	if (!err_msg || !first_join)
	{
		free(err_msg);
		safe_exit(shell, first_join, STR, 2);
	}
	write(2, err_msg, ft_strlen(err_msg));
	free(first_join);
	free(err_msg);
}

int	check_invalid_char(char *s)
{
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (2);
		s++;
	}
	return (0);
}
