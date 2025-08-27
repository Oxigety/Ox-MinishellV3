/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Oxigety_ <Oxigety_@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:14:23 by Oxigety_          #+#    #+#             */
/*   Updated: 2024/07/22 15:14:23 by Oxigety_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_len_var(char *var_value, char *to_free)
{
	int		len_var;

	len_var = ft_strlen(var_value);
	free(var_value);
	free(to_free);
	return (len_var);
}

int	extract_dollar_size(t_shell *shell, char *str, int begin, int end)
{
	char	*to_search;
	char	*var_value;
	int		k;
	int		j;

	k = begin + 1;
	j = 0;
	if (begin == end)
		return (0);
	to_search = malloc(sizeof(char) * (end - begin + 2));
	if (!to_search)
		safe_exit(shell, str, STR, 1);
	while (begin++ <= end)
		to_search[j++] = str[k++];
	to_search[j - 1] = '\0';
	if (ft_strcmp(to_search, "?") == 0)
		var_value = ft_itoa(shell->exitcode);
	else
		var_value = ft_getenv(shell, to_search, to_search);
	if (var_value != NULL)
		return (get_len_var(var_value, to_search));
	free(to_search);
	return (0);
}
