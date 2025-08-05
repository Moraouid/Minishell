/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 08:29:31 by zatais            #+#    #+#             */
/*   Updated: 2025/08/05 14:41:16 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>

char	*generate_filename(t_shell *shell)
{
	char	*filename;
	char	*rand_str;
	int		i;

	i = -1;
	while (++i < 9)
	{
		rand_str = random_str(shell);
		filename = ft_strjoin("/tmp/minishell_heredoc_", rand_str, &shell->gc);
		if (access(filename, F_OK))
			return (filename);
	}
	return (NULL);
}

char	*expand_var_heredoc(t_shell *shell, char *line)
{
	int		i;
	int		start;
	char	*res;
	char	*sub;

	i = 0;
	shell->r_str = ft_strdup("", &shell->gc);
	res = ft_strdup("", &shell->gc);
	while (line[i])
	{
		if (line[i] == '$')
			expand_variable(line, &i, shell, &res);
		else
		{
			start = i;
			while (line[i] && line[i] != '$')
				i++;
			sub = ft_substr(line, start, i - start, &shell->gc);
            res = ft_strjoin(res, sub, &shell->gc);
		}
	}
	return (res);
}

void	heredoc_error(char *delimiter)
{
	ft_putstr_fd("Niggshell: warning: ", 2);
	ft_putstr_fd("here-document delimited by end-of-file", 2);
	ft_putstr_fd(" (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
}

void	write_line(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

void	process_line(t_shell *shell, int fd, char *line, int expand)
{
	char	*expanded;

	if (expand)
	{
		if (find_dollar_sign(line))
		{
			expanded = expand_var_heredoc(shell, line);
			write_line(fd, expanded);
		}
		else
			write_line(fd, line);
	}
	else
		write_line(fd, line);
}

void	write_to_tmp(t_shell *shell, char *delimiter, int fd, int expand)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			heredoc_error(delimiter);
			break ;
		}
		if (!ft_strcmp(delimiter, line))
		{
			free(line);
			break ;
		}
		process_line(shell, fd, line, expand);
		free(line);
	}
}

int	setup_heredoc_file(char **filename, t_shell *shell)
{
	*filename = generate_filename(shell);
	if (!*filename)
		return (perror("Niggshell: heredoc: tmp file failed"), 0);
	return (1);
}

int	handle_heredoc_child(t_shell *shell, t_token *d, int fd, int exp)
{
	int	pid;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		get_signal_index(1);
		setup_signals();
		write_to_tmp(shell, d->value, fd, exp);
		close(fd);
		clean_exit(0, shell);
	}
	get_signal_index(0);
	setup_signals();
	return (pid);
}

int	process_heredoc(t_shell *shell, t_token *delim)
{
	char	*filename;
	int		fd;
	int		pid;
	int		status;
	int		expand;

	expand = (!ft_strchr(delim->value, '"') || !ft_strchr(delim->value, '\''));
	delim->value = remove_quote_delimiter(&shell->gc, delim->value);
	if (!setup_heredoc_file(&filename, shell))
		return (0);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
		return (perror("Niggshell: heredoc: open failed"), 0);
	pid = handle_heredoc_child(shell, delim, fd, expand);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		shell->last_exit_status = WEXITSTATUS(status);
		if (shell->last_exit_status == 130)
			return (0);
	}
	close(fd);
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
