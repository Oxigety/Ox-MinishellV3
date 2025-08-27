/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Oxigety_ <Oxigety_@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:03:46 by Oxigety_          #+#    #+#             */
/*   Updated: 2024/07/25 16:03:47 by Oxigety_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_handler_c(int signum)
{
	(void)signum;
	printf("\n");
	save_shell(NULL, 130);
	rl_replace_line("\0", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	set_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler_c);
}

void	save_shell(int *ex_code, int new_code)
{
	static int	*old_code;

	if (new_code == -1)
		old_code = ex_code;
	else
		*old_code = new_code;
}
