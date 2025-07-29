/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   by: zatais <zatais@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   created: 2025/07/14 02:38:49 by zatais            #+#    #+#             */
/*   Updated: 2025/07/20 20:58:42 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_builtin(t_shell *shell, t_command *cmd)
{
	int	ret;

	ret = 127;
	if (!ft_strncmp(cmd->args[0], "cd", 3))
		ret = my_cd(shell, &cmd->args[1], &shell->gc);
	else if (!ft_strncmp(cmd->args[0], "echo", 5))
		ret = my_echo(&cmd->args[1]);
	else if (!ft_strncmp(cmd->args[0], "env", 4))
		ret = my_env(shell->env, &cmd->args[1]);
	else if (!ft_strncmp(cmd->args[0], "export", 7))
		ret = my_export(&shell->env, &cmd->args[1], &shell->env_gc);
	else if (!ft_strncmp(cmd->args[0], "pwd", 4))
		ret = my_pwd(shell);
	else if (!ft_strncmp(cmd->args[0], "unset", 6))
		ret = my_unset(&shell->env, &cmd->args[1], &shell->env_gc);
	else if (!ft_strncmp(cmd->args[0], "exit", 5))
		ret = my_exit(&cmd->args[1], shell);
	return (ret);
}

void	handle_parent(t_command *cmd, int *next_pipe, int *prev_pipe, int i)
{
	if (i > 0)
		close(*prev_pipe);
	if (cmd->next)
	{
		*prev_pipe = next_pipe[0];
		close(next_pipe[1]);
	}
}

void	handle_child(t_shell *shell, t_command *cur_cmd, int *next_pipe, int prev_pipe, int i)
{
	// signal_handler
	if (i > 0)
	{
		dup2(prev_pipe, 0);
		close(prev_pipe);
	}
	if (cur_cmd->next)
	{
		dup2(next_pipe[1], 1);
		close(next_pipe[0]);
		close(next_pipe[1]);
	}
	exec_child(shell, cur_cmd);
}

void    wait_all(t_shell *shell, int *pids, int count)
{
    int    j;
    int    status;
    int last_status;

    j = 0;
    while (j < count)
    {
        waitpid(pids[j], &status, 0);
        if (j == count -1)
            last_status = status;
        j++;
    }
    if (WIFEXITED(last_status))
        shell->last_exit_status = WEXITSTATUS(last_status);
    else if (WIFSIGNALED(last_status))
        shell->last_exit_status = 128 + WTERMSIG(last_status);
}

void	exec_pipeline(t_shell *shell, int count)
{
	int		next_pipe[2];
	pid_t	*pids;
	int		i;
	int		prev_pipe;// i think i should remove it !!
    t_command *cur_cmd;

	prev_pipe = -1;
	i = 0;
	pids = gc_malloc(&shell->gc, count * sizeof(pid_t));
    cur_cmd = shell->cmd;
	while (cur_cmd)
	{
		if (cur_cmd->next && pipe(next_pipe) == -1)
		{
			perror("minishell");
			break ;
		}
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("minishell: fork");
			if (cur_cmd->next)
			{
				close(next_pipe[0]);
				close(next_pipe[1]);
			}
			break ;
		}
		if (!pids[i])
			handle_child(shell, cur_cmd, next_pipe, prev_pipe, i);
		else
			handle_parent(cur_cmd, next_pipe, &prev_pipe, i);
		cur_cmd = cur_cmd->next;
		i++;
	}
	wait_all(shell, pids, count);
	if (prev_pipe != -1)
		close(prev_pipe);
}

void	start_exec(t_shell *shell)
{
	int	count;

	count = cmd_counter(shell->cmd);
	if (count == 1 && is_builtin(shell->cmd->args[0]))
	{
		shell->stdin_fd = dup(0);
		shell->stdout_fd = dup(1);
		if (!redirect(shell->cmd->redirs))
		{
			shell->last_exit_status = 1;
            ft_putendl_fd("Niggshell: redirection error", 2);
		}
		else
			shell->last_exit_status = execute_builtin(shell, shell->cmd);
		restore_stds(shell->stdin_fd, shell->stdout_fd);
		close(shell->stdin_fd);
		close(shell->stdout_fd);
	}
	else
		exec_pipeline(shell, count);
}
