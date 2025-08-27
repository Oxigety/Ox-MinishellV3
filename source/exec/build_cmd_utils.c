/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Oxigety_ <Oxigety_@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:50:55 by Oxigety_          #+#    #+#             */
/*   Updated: 2024/07/08 12:50:57 by Oxigety_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

int	size_redirection(char *cmd, int *i, int res)
{
	while (cmd[*i])
	{
		if ((cmd[*i] == '>' || cmd[*i] == '<') && !is_in_quotes(cmd, *i))
			break ;
		*i += 1;
	}
	if (!cmd[*i])
		return (0);
	res = *i;
	*i += 1;
	if ((cmd[*i] == '>' || cmd[*i] == '<') && !is_in_quotes(cmd, *i))
		*i += 1;
	while (cmd[*i] && ft_isspace(cmd[*i]))
		*i += 1;
	while (cmd[*i])
	{
		if (ft_isspace(cmd[*i]) && !is_in_quotes(cmd, *i))
			break ;
		*i += 1;
	}
	res = *i - res;
	return (res);
}

char	*clean_command(char *cmd)
{
	char	*result;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (cmd[i])
		len += size_redirection(cmd, &i, 0);
	result = malloc(sizeof(char) * (ft_strlen(cmd) - len + 1));
	if (!result)
		return (NULL);
	copy_without_redirections(cmd, result);
	return (result);
}

t_command	*cmd_last(t_command *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	cmd_node_to_null(t_command *cmd_list)
{
	int	i;

	i = 0;
	cmd_list->input_redirection = NULL;
	cmd_list->output_redirection = NULL;
	if (cmd_list->v_cmd)
	{
		i = 0;
		while (cmd_list->v_cmd[i])
			ft_free(cmd_list->v_cmd[i++]);
		ft_free(cmd_list->v_cmd);
		cmd_list->v_cmd = NULL;
	}
}

void	free_cmd_list(t_command *cmd_list)
{
	t_command	*tmp;

	if (!cmd_list)
		return ;
	cmd_list = cmd_last(cmd_list);
	while (cmd_list)
	{
		tmp = cmd_list->prev;
		ft_free(cmd_list->cmd);
		cmd_list->cmd = NULL;
		if (cmd_list->heredoc_fd > 2)
			close(cmd_list->heredoc_fd);
		ft_free(cmd_list->input_redirection);
		ft_free(cmd_list->output_redirection);
		cmd_node_to_null(cmd_list);
		if (cmd_list->prev)
		{
			ft_free(cmd_list);
			cmd_list = NULL;
		}
		cmd_list = tmp;
	}
}
