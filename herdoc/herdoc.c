/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 08:29:31 by zatais            #+#    #+#             */
/*   Updated: 2025/08/03 08:29:32 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/wait.h>

char	*generate_filename(t_shell *shell)
{
	char	*filename;
	char	*rand;

	rand = random_str(shell);
	filename = ft_strjoin("/tmp/minishell_heredoc_", rand, &shell->gc);
	return (filename);
}

void	heredoc_error(char *delimiter)
{
    ft_putstr_fd("Niggshell: ", 2);
	ft_putstr_fd("warning: ", 2);
	ft_putstr_fd("here-document delimited by end-of-file (wanted`", 2);
    ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
}

void	write_to_tmp(t_shell *shell, char *delimiter, int fd)
{
	char	*line;
	int		i;

	i = 0;
	while (1)
	{
		line = readline("Herdoc--> ");
		++i;
		if (!line)
		{
			heredoc_error(delimiter);
			clean_exit(0, shell);
		}
		if (ft_strncmp(delimiter, line, ft_strlen(delimiter)))
			write(fd, line, ft_strlen(line));
		else
			exit(0);
	}
}

int	heredoc(t_shell *shell)
{
	t_token	*token;
	t_token	*delimiter;
	char	*filename;
	int		fd;
	int		i;
	int		pid;

	token = shell->tokens;
	while (token)
	{
		if (token->type == HEREDOC)
		{
			delimiter = token->next;
            delimiter->value = remove_quote_delimiter(&shell->gc, delimiter->value);
            printf("%s\n", delimiter->value);
			i = -1;
			while (++i < 9)
			{
				filename = generate_filename(shell);
				fd = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0600);
				if (fd >= 0)
					break ;
				if (errno != EEXIST)
				{
					perror("Niggshell");
					return (0);
				}
			}
			pid = fork();
			if (!pid)
				write_to_tmp(shell, delimiter->value, fd);
			waitpid(pid, NULL, 0);
			close(fd);
			delimiter->value = filename;
            token = token->next;
		}
		else
			token = token->next;
	}
	return (1);
}
