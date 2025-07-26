/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:12:49 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/07/01 04:15:19 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	shell_init(t_shell *shell)
{
	shell->r_line = NULL;
	shell->tokens = NULL;
	shell->cmd = NULL;
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	shell.env = NULL;
	copy_env(env, &shell.env, &shell.env_gc);
	while (1337)
	{
		shell_init(&shell);
		shell.r_line = readline("Niggshell~> ");
		if (shell.r_line == NULL)
			exit(0);
		if (ft_strlen(shell.r_line) != 0)
		{
			add_history(shell.r_line);
			parsing_command(&shell);
      start_exec(&shell);
		}
	}
}
