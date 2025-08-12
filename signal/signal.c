/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 07:02:02 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/08/11 12:18:49 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	*get_shell(t_shell *shell)
{
	static t_shell	*save;

	if (shell)
		save = shell;
	return (save);
}

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
		get_shell(NULL)->last_exit_status = 130;
	}
	else if (get_signal_index(-1) == 1)
	{
		write(1, "\n", 1);
		clean_exit(130, get_shell(NULL));
	}
}

void	setup_signals(void)
{
	signal(SIGINT, sighandle);
	signal(SIGQUIT, SIG_IGN);
}
