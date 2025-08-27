/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Oxigety_ <Oxigety_@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:13:01 by Oxigety_          #+#    #+#             */
/*   Updated: 2024/07/22 13:13:02 by Oxigety_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_ctrl(t_shell *shell, int err)
{
	printf("exit\n");
	if (shell->env)
		ft_free_split(shell->env);
	if (shell->list)
		ft_free_env(&shell->list);
	ft_free(shell->str);
	free_heredocs(shell->hdoc_list, false);
	if (shell->heredoc_name)
		free(shell->heredoc_name);
	rl_clear_history();
	if (shell->stdin > 0)
		close(shell->stdin);
	exit(err);
}

void	safe_exit(t_shell *shell, void *param, t_exitflag flag, int err)
{
	int	i;

	i = 0;
	if (flag != NONE)
	{
		if (flag == STR)
			ft_free((char *)param);
		else if (flag == NODE)
			free_nodes((t_env_list *)param);
	}
	free_heredocs(shell->hdoc_list, false);
	ft_free_split(shell->split_path);
	ft_free_split(shell->env);
	ft_free_env(&shell->list);
	if (flag != END)
		ft_free(shell->str);
	free_cmd_list(shell->cmd_list);
	while ((i < 2 * shell->nb_pipes) && shell->pipe_fds)
		close(shell->pipe_fds[i++]);
	ft_free(shell->pipe_fds);
	ft_free(shell->heredoc_name);
	close(shell->stdin);
	rl_clear_history();
	exit(err);
}
