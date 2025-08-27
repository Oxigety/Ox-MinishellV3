/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Oxigety_ <Oxigety_@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:58:47 by Oxigety_          #+#    #+#             */
/*   Updated: 2024/07/08 15:58:48 by Oxigety_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

static void	open_pipes(t_shell *shell, int nb_pipes, int *pipe_fds)
{
	int			i;
	int			tmp;

	i = 0;
	while (i < nb_pipes)
	{
		if (pipe(pipe_fds + (2 * i)) < 0)
		{
			perror("Pipe opening error:\n");
			tmp = 0;
			while (tmp < i)
				close(pipe_fds[tmp++]);
			safe_exit(shell, NULL, NONE, 1);
		}
		i++;
	}
}

static void	wait_parent(t_shell *shell)
{
	int				sig;
	int				status;
	int				i;

	status = 0;
	i = 0;
	while (i < 2 * shell->nb_pipes)
		close(shell->pipe_fds[i++]);
	while (waitpid(0, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			shell->exitcode = (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == 3)
				write(2, "Quit (core dumped)\n", 19);
			if (sig == 2)
				printf("\n");
			if (sig == 2 || sig == 3)
				shell->exitcode = (sig + 128);
		}
	}
}

static void	child_exec(t_shell *shell, t_command *cmd, int *pipe_fds,
						unsigned int i)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (cmd->next)
	{
		if (dup2(pipe_fds[i + 1], STDOUT_FILENO) < 0)
			safe_exit(shell, NULL, NONE, 1);
	}
	if (i != 0)
	{
		if (dup2(pipe_fds[i - 2], STDIN_FILENO) < 0)
			safe_exit(shell, NULL, NONE, 1);
	}
	exec_redirections(shell, cmd, 0);
	if (exec(shell, cmd, pipe_fds) == 1 && *cmd->v_cmd)
		exec_errors(shell, cmd);
	safe_exit(shell, NULL, NONE, shell->exitcode);
}

void	child(t_shell *shell, t_command *cmd, int *pipe_fds, unsigned int i)
{
	int	pid;

	pid = fork();
	if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	if (pid == 0)
		child_exec(shell, cmd, pipe_fds, i);
	else if (pid < 0)
		safe_exit(shell, NULL, NONE, 1);
}

void	pipes_commands(t_shell *shell, t_command *command,
						unsigned int i)
{
	shell->pipe_fds = NULL;
	if (shell->nb_pipes)
	{
		shell->pipe_fds = malloc(sizeof(int) * ((shell->nb_pipes * 2) + 1));
		if (!shell->pipe_fds)
		{
			perror("minishell: malloc: ");
			return ;
		}
		open_pipes(shell, shell->nb_pipes, shell->pipe_fds);
	}
	while (command)
	{
		shell->exitcode = 0;
		if (!handle_command2(shell, command))
			child(shell, command, shell->pipe_fds, i);
		if (dup2(shell->stdin, STDIN_FILENO) < 0)
			perror("dup2 failed : ");
		command = command->next;
		i += 2;
		shell->cmd_lvl++;
	}
	wait_parent(shell);
	ft_free(shell->pipe_fds);
	shell->pipe_fds = NULL;
}
