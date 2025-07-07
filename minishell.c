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

#include "libft/libft.h"
#include "minishell.h"

void	shell_init(t_shell *shell)
{
	shell->r_line = NULL;
	shell->tokens = NULL;
	shell->cmd = NULL;
	shell->red = NULL;
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	shell.env = NULL;
	copy_env(env, &shell.env);
	while (1337)
	{
		shell_init(&shell);
		shell.r_line = readline("sshell->");
		if (shell.r_line == NULL)
			exit(0);
		if (ft_strncmp(shell.r_line, "env", 3) == 0)
		{
			t_env *current = shell.env;
			while (current)
			{
				printf("%s\n", current->value);
				current = current->next;
			}
			free(shell.r_line);
			continue;
		}
		if (ft_strlen(shell.r_line) != 0)
		{
			// printf("%s\n", shell.r_line);
			add_history(shell.r_line);
			parsing_command(&shell);
			free_tokens(&shell);
		}
	}
}
