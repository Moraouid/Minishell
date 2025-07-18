/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:14:06 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/07/17 22:28:59 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <unistd.h>

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
	END
}						t_token_type;

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
	struct s_token		*prev;
}						t_token;

/* ---------------struct of redirction----------- */
typedef struct s_redir
{
	int					type;
	char				*target;
	char				*h_filename;
	struct s_redir		*next;
}						t_redir;

/* ---------------struct of command------------- */

typedef struct s_command
{
	char				**args;
	t_redir				*redirs;
	struct s_command	*next;
}						t_command;

/* ---------------struct of shell-------------- */
typedef struct s_shell
{
	char				*r_line;
	char				*joined_line;
	char				**envp;
	t_token				*tokens;
	t_command			*cmd;
	t_env				*env;
	t_env				*s_env;
}						t_shell;

void					shell_init(t_shell *shell);

/* -----------------parsing_funcion--------------- */
int						is_space(char c);
int						is_operator(char *str, int i);
int						is_separator(char *str, int i);
int						identify_type(char *str, int i);
int						check_syntax_error(char *r_line);
int						copy_env(char **envp, t_env **env);
char					*allocate_word(char *r_line, int *i);
void					expansions(t_shell *shell);
void					free_tokens(t_shell *shell);
void					free_tokens(t_shell *shell);
void					tokeniziation(t_shell *shell);
void					parsing_command(t_shell *shell);
void					add_token(t_token **c_line, t_token *new);
void					add_token(t_token **c_line, t_token *new);
void					handle_quote_error(t_token_status status);
void					print_error(char *msg1, char *msg2, int specific);
t_token					*creat_node_cmd(char *value, int type);
t_token					*creat_node_cmd(char *value, int type);
t_command				*split_commands(t_token *tokens);
void					creat_command(t_shell *shell);
t_token_status			update_quote_status(t_token_status status, char c);
t_command				*split_commands(t_token *tokens);

/* execution */
// void		command_execution(t_read_line *read);

#endif
