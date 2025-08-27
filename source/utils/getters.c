/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Oxigety_ <Oxigety_@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:18:20 by Oxigety_          #+#    #+#             */
/*   Updated: 2024/07/22 13:18:21 by Oxigety_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*grab_var_value(t_shell *shell, char *to_search)
{
	char	*var_value;

	if (ft_strcmp(to_search, "?") == 0)
	{
		var_value = ft_itoa(shell->exitcode);
		if (!var_value)
			shell->exitcode = -1;
	}
	else
		var_value = ft_getenv(shell, to_search, NULL);
	return (var_value);
}

size_t	ft_get_delimiter(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' '
		&& str[i] != '<' && str[i] != '>'
		&& str[i] != '|')
		i++;
	return (i);
}

char	*get_var_name(const char *str)
{
	char	*name;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = malloc(i + 1);
	if (!name)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*get_var_value(char *str)
{
	char	*value;

	value = str;
	while (value[0] != '=')
		value++;
	value++;
	value = ft_strdup(value);
	return (value);
}

int	last_redirection_size(char *cmd, char c, int *start)
{
	int	i;

	i = (int)ft_strlen(cmd);
	while (i >= 0)
	{
		if (cmd[i] == c && !is_in_quotes(cmd, i))
			break ;
		i--;
	}
	if (i == -1)
		return (0);
	while (cmd[i] && ft_isspace(cmd[++i]))
		;
	*start = i;
	while (cmd[i])
	{
		if (ft_isspace(cmd[i]) && !is_in_quotes(cmd, i))
			break ;
		i++;
	}
	return (i - *start);
}
