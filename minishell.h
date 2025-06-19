/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:14:06 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/06/14 18:28:30 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

# include <unistd.h>

// to handel quotes 
// typedef enum e_token_status
// {
// 	DEFAULT,
// 	SQUOTE,
// 	DQUOTE
// }	t_token_status;

typedef enum e_token_type
{
	WORD,
	PIPE,
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND,
	SPACES,
	DQUOTE,
	SQUOTE,
	END
}		t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;


typedef struct s_redir
{
	int     type; // INPUT, OUTPUT, HEREDOC, APPEND
	char    *target; // file or command to redirect to
	char    *content; // content for HEREDOC '??'
	struct s_redir *next;
} t_redir;


typedef struct s_command
{
	char    **args; // echo -n "hello world"
	t_redir *redirs; // redirection list
	struct s_command *next;
	struct s_command *prev;
} t_command;

typedef struct s_shell
{
	char		*r_line;
	t_token     *tokens;
	t_command	*cmd;
	t_redir		*red;
}	t_shell;




void    shell_init(t_shell *shell);


/* parsing_command */
void		parsing_command(t_shell *shell);
void    free_tokens(t_shell *shell);
/* execution */
// void		command_execution(t_read_line *read);

#endif
