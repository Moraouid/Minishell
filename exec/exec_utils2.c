/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:16:13 by zatais            #+#    #+#             */
/*   Updated: 2025/07/29 13:16:13 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd,
			"env") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "echo"))
		return (1);
	return (0);
}

int	cmd_counter(t_command *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		++count;
		cmd = cmd->next;
	}
	return (count);
}


void	exec_child(t_shell *shell, t_command *cur_cmd)
{
	char	*full_path;
	char	**env_array;
    t_gc_node *child_gc;

	if (redirect(cur_cmd->redirs) == -1)
		exit(1);
	if (is_builtin(cur_cmd->args[0]))
	{
		shell->last_exit_status = execute_builtin(shell, cur_cmd);
		gc_clean(&shell->gc);
        gc_clean(&shell->env_gc);
		exit(shell->last_exit_status);
	}
	if (is_not_found(shell, cur_cmd, &full_path))
		exit(127);
	if (dir_perm(full_path, shell) == 1)
		exit(126);
	env_array = convert_env(shell, &shell->gc);
	execve(full_path, cur_cmd->args, env_array);
    cmd_error(full_path, NULL, strerror(errno));
	gc_clean(&shell->gc);
    gc_clean(&shell->env_gc);
    exit(126);
}

