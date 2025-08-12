/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:05:26 by zatais            #+#    #+#             */
/*   Updated: 2025/08/11 19:02:16 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_in(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Niggshell");
		return (0);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

int	open_out(char *filename, t_redir *rd)
{
	int	fd;

	if (rd->type == OUTPUT)
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("Niggshell");
			return (0);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (rd->type == APPEND)
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror("Niggshell");
			return (0);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (1);
}

int	redirect(t_redir *rd)
{
	char	*filename;

	while (rd)
	{
		filename = rd->target;
		if (rd->type == HEREDOC)
			filename = rd->h_filename;
		if (rd->type == INPUT || rd->type == HEREDOC)
		{
			if (!open_in(filename))
				return (0);
		}
		else if (!open_out(filename, rd))
			return (0);
		rd = rd->next;
	}
	return (1);
}

void	restore_stds(int stdin, int stdout)
{
	dup2(stdin, STDIN_FILENO);
	dup2(stdout, STDOUT_FILENO);
}
