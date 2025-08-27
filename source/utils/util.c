/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchapuis <bchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:40:05 by bchapuis          #+#    #+#             */
/*   Updated: 2024/05/21 14:55:32 by bchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*next_redirection_name(t_command *cmd, int i)
{
	int		len;
	char	*redirection;

	while (cmd->cmd[i] == '<' || cmd->cmd[i] == '>' || ft_isspace(cmd->cmd[i]))
		i++;
	len = 0;
	while (cmd->cmd[i + len] && (!ft_isspace(cmd->cmd[i + len])
			|| is_in_quotes(cmd->cmd, i + len)))
		len++;
	redirection = malloc(sizeof(char) * (len + 1));
	if (!redirection)
		return (NULL);
	redirection[len] = '\0';
	while (--len >= 0)
		redirection[len] = cmd->cmd[i + len];
	if (is_there_chr(redirection, '\'') || is_there_chr(redirection, '"'))
		redirection = str_without_quotes(redirection);
	return (redirection);
}

bool	check_last_redirection(char *str, char c)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c && !is_in_quotes(str, i))
			return (false);
		i++;
	}
	return (true);
}

bool	var_is_valid(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[0]) || str[0] == '_')
	{
		while (str[i] && str[i] != '=')
		{
			if (str[i] < 48 || (str[i] >= 58 && str[i] <= 64)
				|| (str[i] >= 91 && str[i] <= 96)
				|| (str[i] > 122))
			{
				if (str[i] != '_' && str[i] != ' ')
					return (false);
			}
			i++;
		}
		return (true);
	}
	return (false);
}

bool	handle_isspace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\f'
			|| str[i] == '\n' || str[i] == '\r'
			|| str[i] == '\t' || str[i] == '\v')
		{
			i++;
		}
		else
			return (false);
	}
	free(str);
	return (true);
}

void	free_nodes(t_env_list *node)
{
	ft_free(node->var_name);
	ft_free(node->value);
	ft_free(node);
}
