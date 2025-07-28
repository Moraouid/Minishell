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

    shell->last_exit_status = 0;
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	shell.env = NULL;
    shell.gc = NULL;
    shell.env_gc = NULL;
    shell.last_exit_status = 0;
	if (!copy_env(env, &shell.env, &shell.env_gc))
		return (0);
	while (1337)
	{
        shell_init(&shell);
		shell.r_line = readline("Niggshell~> ");
		if (!shell.r_line)
        {
            gc_clean(&shell.gc);
            gc_clean(&shell.env_gc);
            ft_putstr_fd("exit\n", 1);
			exit(shell.last_exit_status);
        }
		gc_add(&shell.gc, shell.r_line);
		if (ft_strlen(shell.r_line))
		{
			add_history(shell.r_line);
			if(parsing_command(&shell))
			    start_exec(&shell);
			parsing_command(&shell);
			start_exec(&shell);
		}
		gc_clean(&shell.gc);
	}
	gc_clean(&shell.env_gc);
}
