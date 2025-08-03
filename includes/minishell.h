/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 07:54:04 by zatais            #+#    #+#             */
/*   Updated: 2025/08/03 16:25:33 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "exec.h"
# include "parse.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdbool.h>

/* ----------------enum of errno--------------- */
typedef enum e_errno
{
	ERRNO_DQ,
	ERRNO_SQ,
	ERRNO_RD,
	ERRNO_AR,
	ERRNO_A,
	ERRNO_P,
}						t_errno;

/* ---------------enum of token status--------- */
typedef enum e_token_status
{
	DEFAULT,
	SQUOTE,
	DQUOTE
}						t_token_status;

/* ---------------enum of token type----------- */
typedef enum e_token_type
{
	WORD,
	PIPE,
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND,
	SPACES,
	AMBGUS,
	END
}						t_token_type;

/* -------------struct of quotes flag---------- */
typedef struct s_quotes_flag
{
	int					i;
	int					j;
	int					sq;
	int					dq;
	int					rq;
	int					len;
	int					start;
}						t_quotes;

/* --------------struct of env----------------- */
typedef struct s_env
{
	char				*value;
	struct s_env		*next;
}						t_env;

/* ---------------struct of token-------------- */
typedef struct s_token
{
	char				*value;
	t_token_type		type;
	struct s_token		*next;
}						t_token;

/* -------------struct of redirction----------- */
typedef struct s_redir
{
	int					type;
	int					f_ambiguous;
	char				*target;
	char				*h_filename;
	struct s_redir		*next;
}						t_redir;

/* --------------struct of command------------- */

typedef struct s_command
{
	char				**args;
	t_redir				*redirs;
	struct s_command	*next;
}						t_command;

/* ---------------struct of g_col-------------- */
typedef struct s_gc_node
{
	void				*ptr;
	struct s_gc_node	*next;
}						t_gc_node;

/* ---------------struct of shell-------------- */
typedef struct s_shell
{
	int					last_exit_status;
	int					stdout_fd;
	int					stdin_fd;
	char				**envp;
	char				*r_line;
	char				*r_str;
	char				*joined_line;
	char				*cwd;
	t_env				*env;
	t_env				*s_env;
	t_token				*tokens;
	t_gc_node			*gc;
	t_gc_node			*env_gc;
	t_command			*cmd;
}						t_shell;

#endif
