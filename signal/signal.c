/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 07:02:02 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/08/05 07:02:02 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	get_signal_index(int state)
{
	static int	data;

	if (state != -1)
		data = state;
	return (data);
}

void	sighandle(int sig)
{
	(void)sig;
	if (get_signal_index(-1) == 0)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (get_signal_index(-1) == 1)
	{
		write(1, "\n", 1);
		exit(130);
	}
}

void setup_signals(void)
{
	signal(SIGINT, sighandle);
	signal(SIGQUIT, SIG_IGN);
}

