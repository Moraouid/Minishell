/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:14:06 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/06/09 20:50:56 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <unistd.h>

typedef enum e_type {
	WORD,
	PIPE,
	RED_IN,
	RED_OUT,
	HERDOC,
	APPEND,
	STRING,
	TARGET,
}   t_type;

typedef struct s_redir
{
	int     type;
	char    *target;
	char    *content;
	struct s_redir *next;
} t_redir;

typedef struct s_command
{
	char    **args;
	t_redir *redirs;
	struct s_command *next;
} t_command;

typedef struct s_token
{
	char    *cmd;
	t_type  type;
	struct s_token *next;
	struct s_token *prev;
}   t_token;

typedef struct s_shell
{
	char		*r_line;
	t_token     *token;
	t_command	*cmd;
	t_redir		*red;
}	t_shell;

void    shell_init(t_shell *shell);


/* parsing_command */
void		parsing_command(t_shell *shell);

/* execution */
// void		command_execution(t_read_line *read);

#endif