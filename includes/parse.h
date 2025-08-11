/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 03:54:51 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/08/08 10:59:52 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef struct s_shell			t_shell;
typedef struct s_token			t_token;
typedef struct s_command		t_command;
typedef struct s_quotes_flag	t_quotes;
typedef struct s_gc_node		t_gc_node;
typedef struct s_gc_node		t_gc_node;
typedef enum e_errno			t_errno;
typedef enum e_token_status		t_token_status;

/* --------------utils functions-------------- */
int					is_space(char c);
char				*random_str(t_shell *shell);
char				*ft_itoa(int n, t_gc_node **gc);
char				*ft_substr(char *s, int start, int len, t_gc_node **gc);
void				init_flag(t_quotes *flag);
void				shell_init(t_shell *shell);
void				add_token(t_token **c_line, t_token *new);
void				add_back_cmd(t_command **cmd, t_command *n_cmd);
void				print_error(t_shell *shell, t_errno ty_errno,	char *str);
t_token				*creat_node_cmd(t_shell *shell, char *value, int type);
/* ------------expansions functions----------- */
int					find_dollar_sign(char *str);
int					count_for_split(t_gc_node **gc, char *value, char *r_str);
void				expand_variable(char *value, int *i, t_shell *shell,
						char **res);
void				remove_expand_quotes(t_token *tokens, char *r_str,
						t_gc_node **gc);
void				split_after_expand(t_shell *shell, t_token *tokens,
						char *j_str);
/* -------------signals funcions-------------- */
int					get_signal_index(int state);
void				sighandle(int sig);
void				setup_signals(void);
void				expansions(t_shell *shell);
/* ---------------parssing functions---------- */
int					isredirction(t_token *token);
int					is_operator(char *str, int i);
int					is_separator(char *str, int i);
int					tokeniziation(t_shell *shell);
int					parsing_command(t_shell *shell);
int					identify_type(char *str, int i);
int					count_word_list(t_token **token);
int					check_quots(t_shell *shell, char *r_line);
int					check_syntax_error(t_shell *shell, t_token *token);
char				*allocate_word(t_shell *shell, char *r_line, int *i);
void				creat_command(t_shell *shell);
void				remove_quotes(t_shell *shell);
void				handle_quote_error(t_token_status status);
t_token_status		update_quote_status(t_token_status status, char c);
/* ---------------heredoc function------------ */
void				write_to_tmp(t_shell *shell, char *delimiter, int fd,
						int expand);

#endif
