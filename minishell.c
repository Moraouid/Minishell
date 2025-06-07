/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:12:49 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/06/07 00:43:34 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	(void)env;
	while (1337)
	{
		shell.r_line = readline("sshell->");
		if(shell.r_line == NULL)
			exit(0);
		if(ft_strlen(shell.r_line) != 0)
		{
			add_history(shell.r_line);
			parsing_command(&shell);
		}
	}
}
