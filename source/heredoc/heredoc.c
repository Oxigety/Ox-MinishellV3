/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babou <babou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 12:15:50 by babou             #+#    #+#             */
/*   Updated: 2024/06/10 11:37:38 by babou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_sig_val;

void	set_gl_var(int signum)
{
	t_shell	*addr;

	if (signum == SIGINT)
	{
		g_sig_val = SIGINT;
		printf("\n");
		rl_replace_line("\0", 0);
		rl_on_new_line();
		rl_redisplay();
		addr = free_shell_addr(NULL, NULL, NULL, true);
		free_heredocs(addr->hdoc_list, false);
		close(addr->stdin);
		if (addr->heredoc_name)
			free(addr->heredoc_name);
		exit(130);
	}
	else
		g_sig_val = 0;
}

char	*analyse_sig_return(t_shell *shell, char *t_free, char *delimiter)
{
	char	*content;

	content = NULL;
	if (g_sig_val != 130)
	{
		content = copy_file_into_content(shell, t_free, delimiter);
		unlink("fork_content.tmp");
	}
	set_signals();
	return (content);
}

char	*read_heredoc(t_shell *shell, char *delimiter, char *t_free)
{
	int		pid;
	int		status;
	char	*content;

	signal(SIGINT, set_gl_var);
	pid = fork();
	if (pid == 0)
		heredoc_fork(shell, delimiter, t_free);
	else if (pid < 0)
		safe_exit(shell, NULL, NONE, 2);
	else
	{
		signal(SIGINT, SIG_IGN);
		if (waitpid(pid, &status, 0) > 0)
		{
			if (WIFEXITED(status))
				g_sig_val = WEXITSTATUS(status);
			save_shell(NULL, g_sig_val);
			set_signals();
		}
	}
	content = analyse_sig_return(shell, t_free, delimiter);
	return (content);
}

bool	heredoc_was_inter(char *str)
{
	if (g_sig_val == 130)
	{
		g_sig_val = 0;
		free(str);
		return (true);
	}
	else
		return (false);
}

int	handle_heredoc(t_shell *shell, char *delimiter, char *t_free)
{
	char	*content;

	g_sig_val = 0;
	content = read_heredoc(shell, delimiter, t_free);
	if (heredoc_was_inter(content))
		return (0);
	if (!content)
	{
		free(delimiter);
		safe_exit(shell, t_free, STR, 2);
	}
	check_heredoc_existence(shell, t_free, delimiter, content);
	return (1);
}
