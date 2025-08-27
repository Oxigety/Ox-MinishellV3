/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Oxigety_ <Oxigety_@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:06:56 by Oxigety_          #+#    #+#             */
/*   Updated: 2024/07/25 15:06:57 by Oxigety_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

void	ft_free_env(t_env_list **head)
{
	t_env_list	*temp;

	if (!head)
		return ;
	while (*head != NULL)
	{
		temp = *head;
		ft_free(temp->value);
		ft_free(temp->var_name);
		*head = (*head)->next;
		ft_free(temp);
	}
}

void	ft_free_split(char **m_tab)
{
	int	i;

	i = 0;
	if (!m_tab)
		return ;
	while (m_tab[i])
	{
		if (m_tab[i] != NULL)
			free(m_tab[i]);
		i++;
	}
	free(m_tab);
}

char	*strjoin_and_free(char *s1, const char *s2)
{
	char	*new_str;
	char	*temp_str;

	if (!s1 || !s2)
		return (NULL);
	temp_str = ft_strjoin(s1, " ");
	if (!temp_str)
		return (NULL);
	new_str = ft_strjoin(temp_str, s2);
	free(temp_str);
	free(s1);
	return (new_str);
}

void	free_heredocs(t_heredoc *heredocs, bool to_unlink)
{
	t_heredoc	*current;
	t_heredoc	*next;

	if (heredocs == NULL)
		return ;
	current = heredocs;
	while (current != NULL)
	{
		next = current->next;
		if (to_unlink && current->filename)
			unlink(current->filename);
		free(current->delim);
		free(current->filename);
		free(current);
		current = next;
	}
}
