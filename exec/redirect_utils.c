/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:05:26 by zatais            #+#    #+#             */
/*   Updated: 2025/07/29 13:05:26 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_in(int *fd, char *filename)
{
	*fd = open(filename, O_RDONLY);
	if (*fd == -1)
	{
		perror("minishell");
		return (0);
	}
	dup2(*fd, 0);
	close(*fd);
	return (1);
}

int	open_out(int *fd, char *filename, t_redir *rd)
{
	if (rd->type == OUTPUT)
	{
		*fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*fd == -1)
		{
			perror("minishell");
			return (0);
		}
		dup2(*fd, 1);
		close(*fd);
	}
	else if (rd->type == APPEND)
	{
		*fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (*fd == -1)
		{
			perror("minishell");
			return (0);
		}
		dup2(*fd, 1);
		close(*fd);
	}
	return (1);
}

int	redirect(t_redir *rd)
{
	int		fd;
	char	*filename;

	while (rd)
	{
		filename = rd->target;
		if (rd->type == HEREDOC)
			filename = rd->h_filename;
		if (rd->type == INPUT || rd->type == HEREDOC)
		{
			if (!open_in(&fd, filename))
				return (0);
		}
		else if (!open_out(&fd, filename, rd))
			return (0);
		rd = rd->next;
	}
	return (1);
}

void	restore_stds(int stdin, int stdout)
{
	dup2(stdin, 1);
	dup2(stdout, 0);
}
