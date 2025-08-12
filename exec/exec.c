/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:19:34 by zatais            #+#    #+#             */
/*   Updated: 2025/08/11 17:47:46 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_builtin(t_shell *shell, t_command *cmd)
{
	int	ret;

	ret = 127;
	if (!ft_strncmp(cmd->args[0], "cd", 3))
		ret = my_cd(shell, &cmd->args[1]);
	else if (!ft_strncmp(cmd->args[0], "echo", 5))
		ret = my_echo(&cmd->args[1]);
	else if (!ft_strncmp(cmd->args[0], "env", 4))
		ret = my_env(shell->env);
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

void	wait_all(t_shell *shell, int *pids, int count)
{
	int	j;
	int	status;
	int	last_status;
	int	err_flag;

	j = 0;
	err_flag = 0;
	while (j < count)
	{
		waitpid(pids[j], &status, 0);
		if (j == count - 1)
			last_status = status;
		if (WTERMSIG(status) == SIGINT && !err_flag)
		{
			err_flag = 1;
			write(1, "\n", 1);
		}
		j++;
	}
	if (WIFEXITED(last_status))
		shell->last_exit_status = WEXITSTATUS(last_status);
	else if (WIFSIGNALED(last_status))
		shell->last_exit_status = 128 + WTERMSIG(last_status);
	if (WTERMSIG(last_status) == SIGQUIT)
		write(1, "Quit (core dumped)\n", 19);
}

int	setup_pipe(t_command *cmd, int *pipes)
{
	int	new_pipe[2];

	if (!cmd->next)
		return (1);
	if (pipe(new_pipe) == -1)
	{
		perror("Niggshell");
		return (0);
	}
	pipes[1] = new_pipe[0];
	pipes[2] = new_pipe[1];
	return (1);
}

void	exec_pipeline(t_shell *shell, int count)
{
	int			pipes[3];
	pid_t		*pids;
	int			i;
	t_command	*cur_cmd;

	pipes[0] = -1;
	i = -1;
	pids = gc_malloc(&shell->gc, count * sizeof(pid_t));
	cur_cmd = shell->cmd;
	while (cur_cmd)
	{
		if (!setup_pipe(cur_cmd, pipes))
			break ;
		signal(SIGINT, SIG_IGN);
		pids[++i] = fork();
		if (fork_err(cur_cmd, pids[i], pipes))
			break ;
		if (pids[i] == 0)
			child_process(shell, cur_cmd, pipes);
		else
			parent_process(cur_cmd, pipes);
		cur_cmd = cur_cmd->next;
	}
	wait_all(shell, pids, count);
}

void	start_exec(t_shell *shell)
{
	int	count;

	count = cmd_counter(shell->cmd);
	if (count == 1 && shell->cmd->args[0] && is_builtin(shell->cmd->args[0]))
	{
		shell->stdin_fd = dup(STDIN_FILENO);
		shell->stdout_fd = dup(STDOUT_FILENO);
		if (!redirect(shell->cmd->redirs))
			shell->last_exit_status = 1;
		else
			shell->last_exit_status = execute_builtin(shell, shell->cmd);
		restore_stds(shell->stdin_fd, shell->stdout_fd);
		close(shell->stdin_fd);
		close(shell->stdout_fd);
	}
	else
		exec_pipeline(shell, count);
}
