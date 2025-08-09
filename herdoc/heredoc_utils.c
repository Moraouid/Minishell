/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 10:42:26 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/08/08 11:52:48 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
