/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 08:29:31 by zatais            #+#    #+#             */
/*   Updated: 2025/08/10 19:05:47 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*generate_filename(t_shell *shell)
{
	char	*filename;
	char	*rand_str;
	int		i;

	i = -1;
	while (++i < 9)
	{
		rand_str = random_str(shell);
		filename = ft_strjoin("/tmp/.heredoc_", rand_str, &shell->gc);
		if (access(filename, F_OK))
			return (filename);
	}
	return (NULL);
}

int	handle_heredoc_child(t_shell *shell, t_token *d, int fd, int exp)
{
	int	pid;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (!pid)
	{
		get_signal_index(1);
		setup_signals();
		write_to_tmp(shell, d->value, fd, exp);
		close(fd);
		clean_exit(0, shell);
	}
	return (pid);
}

int	wait_heredoc(t_shell *shell, int pid, int *fd)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->last_exit_status = 128 + WTERMSIG(status);
	if (shell->last_exit_status == 130)
	{
		close(*fd);
		*fd = -1;
		return (0);
	}
	return (1);
}

int	process_heredoc(t_shell *shell, t_token *delim)
{
	char	*filename;
	int		fd;
	int		pid;
	int		expand;

	expand = (!ft_strchr(delim->value, '"') && !ft_strchr(delim->value, '\''));
	if (!expand)
		delim->value = remove_quote_delimiter(&shell->gc, delim->value);
	if (!setup_heredoc_file(&filename, shell))
		return (0);
	fd = open(filename, O_CREAT | O_WRONLY, 0600);
	shell->herdoc_fd = fd;
	if (fd < 0)
		return (perror("Niggshell: heredoc: open failed"), 0);
	pid = handle_heredoc_child(shell, delim, fd, expand);
	if (!wait_heredoc(shell, pid, &shell->herdoc_fd))
		return (0);
	close(shell->herdoc_fd);
	shell->herdoc_fd = -1;
	delim->value = filename;
	return (1);
}

int	heredoc(t_shell *shell)
{
	t_token	*token;

	token = shell->tokens;
	while (token)
	{
		if (token->type == HEREDOC)
		{
			if (!process_heredoc(shell, token->next))
				return (0);
			token = token->next;
		}
		token = token->next;
	}
	return (1);
}
