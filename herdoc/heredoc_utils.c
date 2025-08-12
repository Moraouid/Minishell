/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 10:42:26 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/08/11 16:09:11 by sel-abbo         ###   ########.fr       */
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

void	process_line(t_shell *shell, int fd, char *line, int expand)
{
	char	*expanded;

	if (!expand && find_dollar_sign(line))
	{
		expanded = expand_var_heredoc(shell, line);
		ft_putendl_fd(expanded, fd);
	}
	else
		ft_putendl_fd(line, fd);
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
