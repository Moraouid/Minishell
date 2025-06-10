/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:12:49 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/06/09 21:20:28 by sel-abbo         ###   ########.fr       */
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
	(void)env;
	while (1337)
	{
		shell_init(&shell);
		shell.r_line = readline("sshell->");
		if (shell.r_line == NULL)
			exit(0);
		if (ft_strlen(shell.r_line) != 0)
		{
			printf("%s", shell.r_line);
			if (!strcmp(shell.r_line, "!"))
			{
				free_tokens(&shell);
				exit(0);
			}
			add_history(shell.r_line);
			parsing_command(&shell);
			free_tokens(&shell);
		}
	}
}
