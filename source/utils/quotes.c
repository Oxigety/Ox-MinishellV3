/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Oxigety_ <Oxigety_@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:56:53 by Oxigety_          #+#    #+#             */
/*   Updated: 2024/07/16 13:56:55 by Oxigety_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_quotes(const char *str)
{
	int	i;
	int	qts;
	int	count;

	i = 0;
	qts = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && qts == 0)
		{
			if (str[i] == '\'')
				qts--;
			else
				qts++;
			count++;
		}
		else if ((str[i] == '\'' && qts == -1) || (str[i] == '"' && qts == 1))
		{
			qts = 0;
			count++;
		}
		i++;
	}
	return (count);
}
