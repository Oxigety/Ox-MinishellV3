/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Oxigety_ <Oxigety_@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:20:59 by Oxigety_          #+#    #+#             */
/*   Updated: 2024/07/19 14:21:00 by Oxigety_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	input_redirection(t_shell *shell, t_command *cmd,
	int pipe_fd, int i)
{
	int		fd;
	char	*path;

	(void)pipe_fd;
	path = next_redirection_name(cmd, i);
	if (!path)
	{
		perror("minishell: malloc: ");
		exit(2);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(path);
		if (cmd->next)
			safe_exit(shell, path, STR, 0);
		safe_exit(shell, path, STR, 1);
	}
	if (!ft_strncmp(path, cmd->input_redirection, ft_strlen(path))
		&& check_last_redirection(cmd->cmd + i, '<'))
		if (dup2(fd, STDIN_FILENO) < 0)
			safe_exit(shell, path, STR, 1);
	free(path);
	close(fd);
}

void	heredoc_redirection(t_shell *shell, t_command *cmd, int i)
{
	char		*delim;
	t_heredoc	*current_heredoc;

	delim = next_redirection_name(cmd, i);
	if (!delim)
		safe_exit(shell, delim, STR, 2);
	current_heredoc = shell->hdoc_list;
	while (current_heredoc)
	{
		if (ft_strcmp(current_heredoc->delim, delim) == 0
			&& shell->cmd_lvl == current_heredoc->pipe_pos)
		{
			cmd->heredoc_fd = open(current_heredoc->filename, O_RDONLY, 0666);
			if (cmd->heredoc_fd < 0)
				perror("minishell: heredocument");
			if (dup2(cmd->heredoc_fd, STDIN_FILENO) < 0)
				safe_exit(shell, delim, STR, 1);
			close(cmd->heredoc_fd);
			break ;
		}
		current_heredoc = current_heredoc->next;
	}
	free(delim);
}

void	trunc_redirection(t_shell *shell, t_command *cmd, int pipe_fd, int i)
{
	int		fd;
	char	*path;

	path = next_redirection_name(cmd, i);
	if (!path)
	{
		perror("minishell: malloc: ");
		exit(2);
	}
	fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0600);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(path);
		if (cmd->next)
			safe_exit(shell, path, STR, 0);
		safe_exit(shell, path, STR, 1);
	}
	if (!ft_strncmp(path, cmd->output_redirection, ft_strlen(path))
		&& check_last_redirection(cmd->cmd + i, '>'))
		if (dup2(fd, pipe_fd) < 0)
			safe_exit(shell, path, STR, 1);
	free(path);
	close(fd);
}

void	append_redirection(t_shell *shell, t_command *cmd, int pipe_fd, int i)
{
	int		fd;
	char	*path;

	path = next_redirection_name(cmd, i);
	if (!path)
	{
		perror("minishell: malloc: ");
		exit(2);
	}
	fd = open(path, O_CREAT | O_APPEND | O_WRONLY, 0600);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(path);
		safe_exit(shell, path, STR, 1);
	}
	if (!ft_strncmp(path, cmd->output_redirection, ft_strlen(path))
		&& check_last_redirection(cmd->cmd + i, '>'))
		if (dup2(fd, pipe_fd) < 0)
			safe_exit(shell, path, STR, 1);
	free(path);
	close(fd);
}

void	in_out_redirection(t_shell *shell, t_command *command,
	int pipe_fd, int i)
{
	if (command->cmd[i] == '>' || command->cmd[i] == '<')
		i++;
	if (command->cmd[i - 1] == '>' && command->cmd[i] == '>')
		append_redirection(shell, command, pipe_fd, i + 1);
	else if (command->cmd[i - 1] == '>')
		trunc_redirection(shell, command, pipe_fd, i);
	else if (command->cmd[i - 1] == '<' && command->cmd[i] == '<')
		heredoc_redirection(shell, command, i);
	else if (command->cmd[i - 1] == '<')
		input_redirection(shell, command, pipe_fd, i);
}
