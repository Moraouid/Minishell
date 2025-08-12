/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:16:13 by zatais            #+#    #+#             */
/*   Updated: 2025/08/12 12:17:04 by sel-abbo         ###   ########.fr       */
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

void	clean_exit(int status, t_shell *shell)
{
	if (shell->herdoc_fd != -1)
		close(shell->herdoc_fd);
	gc_clean(&shell->gc);
	gc_clean(&shell->env_gc);
	exit(status);
}

void	exec_child(t_shell *shell, t_command *cur_cmd)
{
	char	*full_path;
	char	**env_array;

	if (!redirect(cur_cmd->redirs))
		clean_exit(1, shell);
	if (cur_cmd->args[0] && is_builtin(cur_cmd->args[0]))
	{
		shell->last_exit_status = execute_builtin(shell, cur_cmd);
		clean_exit(shell->last_exit_status, shell);
	}
	if (!cur_cmd->args[0])
		clean_exit(0, shell);
	is_not_found(shell, cur_cmd, &full_path);
	check_perm(full_path, shell);
	env_array = convert_env(shell, &shell->gc);
	execve(full_path, cur_cmd->args, env_array);
	cmd_error(full_path, NULL, strerror(errno), &shell->gc);
	clean_exit(126, shell);
}

int	is_dir(char *full_path)
{
	struct stat	statbuf;

	if (!stat(full_path, &statbuf))
		return (S_ISDIR(statbuf.st_mode));
	return (0);
}
