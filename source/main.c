/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchapuis <bchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:44:49 by bchapuis          #+#    #+#             */
/*   Updated: 2024/05/21 15:24:09 by bchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_and_exec(t_shell *shell)
{
	if (process_message(shell))
		return ;
	pipes_commands(shell, shell->cmd_list, 0);
	free_heredocs(shell->hdoc_list, true);
	init_list_heredoc(NULL, NULL, NULL, -1);
	moove_into_next_redir(NULL, NULL, true);
	shell->saved_index = 0;
	shell->heredoc_counter = 0;
	shell->hdoc_list = NULL;
	shell->cmd_lvl = 0;
	ft_free(shell->heredoc_name);
	shell->heredoc_name = NULL;
	free_cmd_list(shell->cmd_list);
	ft_free(shell->str);
	shell->str = NULL;
	shell->str = NULL;
}

void	dup_and_env(t_shell *shell, char **envp)
{
	shell->cmd_list->cmd = NULL;
	shell->cmd_list->v_cmd = NULL;
	shell->cmd_list->heredoc_fd = 0;
	shell->cmd_list->input_redirection = NULL;
	shell->cmd_list->output_redirection = NULL;
	shell->cmd_list->next = NULL;
	shell->cmd_list->prev = NULL;
	shell->hdoc_list = NULL;
	shell->split_path = NULL;
	shell->list = NULL;
	shell->pipe_fds = NULL;
	shell->heredoc_name = NULL;
	shell->saved_index = 0;
	shell->stdin = -1;
	save_shell(&(shell->exitcode), -1);
	init_envp(shell, envp);
	shell->stdin = dup(STDIN_FILENO);
	if (shell->stdin < 0)
		exit_ctrl(shell, 1);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;
	t_command	c_list;

	(void)argc;
	(void)argv;
	ft_memset(&shell, 0, sizeof(t_shell));
	shell.cmd_list = &c_list;
	dup_and_env(&shell, envp);
	while (shell.exit == 0)
	{
		set_signals();
		shell.str = ft_read_input(&shell);
		if (shell.str && shell.str[0] == '\0')
		{
			free(shell.str);
			continue ;
		}
		if (shell.str != NULL)
			get_and_exec(&shell);
		else
			exit_ctrl(&shell, shell.exitcode);
	}
	safe_exit(&shell, NULL, END, shell.exitcode);
	return (0);
}
