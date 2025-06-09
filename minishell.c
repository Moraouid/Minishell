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

#include "minishell.h"

void	shell_init(t_shell *shell)
{
	shell->r_line = NULL;
	shell->token = NULL;
	shell->cmd = NULL;
	shell->red = NULL;
}
void free_token_list(t_token *head) {
    t_token *tmp;

    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp->cmd);
        free(tmp);
    }
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
		if(shell.r_line == NULL)
			exit(0);
		if(ft_strlen(shell.r_line) != 0)
		{
			add_history(shell.r_line);
			parsing_command(&shell);
			free_token_list(shell.token);
		}
	}
}
