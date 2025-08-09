/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 06:29:07 by zatais            #+#    #+#             */
/*   Updated: 2025/08/08 10:10:43 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	fork_err(t_command *cur_cmd, int pid, int *pipes)
{
	if (pid == -1)
	{
		perror("Niggshell: fork");
		if (cur_cmd->next)
		{
			close(pipes[1]);
			close(pipes[2]);
		}
		return (1);
	}
	return (0);
}

void	parent_process(t_command *cmd, int *pipes)
{
	if (pipes[0] != -1)
		close(pipes[0]);
	if (cmd->next)
	{
		pipes[0] = pipes[1];
		close(pipes[2]);
	}
	else
		pipes[0] = -1;
}

void	child_process(t_shell *shell, t_command *cmd, int *pipes)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (pipes[0] != -1)
	{
		dup2(pipes[0], STDIN_FILENO);
		close(pipes[0]);
	}
	if (cmd->next)
	{
		dup2(pipes[2], STDOUT_FILENO);
		close(pipes[2]);
		close(pipes[1]);
	}
	exec_child(shell, cmd);
}
