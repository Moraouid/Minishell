/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 08:00:31 by zatais            #+#    #+#             */
/*   Updated: 2025/08/12 23:30:16 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_env		t_env;
typedef struct s_shell		t_shell;
typedef struct s_redir		t_redir;
typedef struct s_gc_node	t_gc_node;
typedef struct s_command	t_command;

int							is_space(char c);
int							ft_isalnum(int c);
int							ft_isalpha(int c);
int							my_env(t_env *env);
int							my_echo(char **args);
int							redirect(t_redir *rd);
int							is_builtin(char *cmd);
int							my_pwd(t_shell *shell);
int							is_dir(char *full_path);
int							heredoc(t_shell *shell);
int							is_full_alpha(char *val);
int							args_counter(char **args);
int							cmd_counter(t_command *cmd);
int							valid_identifier(char *name);
int							ft_strcmp(char *s1, char *s2);
int							my_cd(t_shell *shell, char **args);
int							long_err(char *cmd, t_gc_node **gc);
int							my_exit(char **args, t_shell *shell);
int							compare_env_vars(char *s1, char *s2);
int							ft_strncmp(char *s1, char *s2, size_t n);
int							execute_builtin(t_shell *shell, t_command *cmd);
int							fork_err(t_command *cur_cmd, int pid, int *pipes);
int							copy_env(char **envp, t_env **env, t_gc_node **gc);
int							my_unset(t_env **env, char **args, t_gc_node **gc);
int							my_export(t_env **env, char **args, t_gc_node **gc);
int							create_new_node(t_env **env, char *arg,
								t_gc_node **gc);
/*----------------------------------------------------------------------------*/
size_t						ft_strlen(char *s);
long						ft_atol(char *arg, int *overflow);
/*----------------------------------------------------------------------------*/
void						sort_env(t_env *exp);
void						cmd_error2(char *arg);
void						gc_clean(t_gc_node **gc);
void						start_exec(t_shell *shell);
void						print_sorted_env(t_env *exp);
void						ft_putstr_fd(char *s, int fd);
void						ft_putendl_fd(char *s, int fd);
void						gc_add(t_gc_node **gc, void *ptr);
void						add_back(t_env **env, t_env *new);
void						restore_stds(int stdin, int stdout);
void						gc_remove(t_gc_node **gc, void *ptr);
void						clean_exit(int status, t_shell *shell);
void						*gc_malloc(t_gc_node **gc, size_t size);
void						parent_process(t_command *cmd, int *pipes);
void						check_perm(char *full_path, t_shell *shell);
void						exec_child(t_shell *shell, t_command *cur_cmd);
void						copy_sort(t_env *env, t_env **exp, t_gc_node **gc);
void						child_process(t_shell *shell, t_command *cmd,
								int *pipes);
void						is_not_found(t_shell *shell, t_command *cur_cmd,
								char **full_path);
void						cmd_error(char *cmd_name, char *error_arg,
								char *error_msg, t_gc_node **gc);
/*---------------------------------------------------------------------------*/
char						*ft_strchr(char *s, int c);
char						*generate_filename(t_shell *shell);
char						*ft_strdup(char *s, t_gc_node **gc);
char						*get_env_value(t_env *env, char *key);
char						**ft_split(char *s, char c, t_gc_node **gc);
char						**convert_env(t_shell *shell, t_gc_node **gc);
char						*ft_strndup(char *s, size_t n, t_gc_node **gc);
char						*ft_strjoin(char *s1, char *s2, t_gc_node **gc);
char						*remove_quote_delimiter(t_gc_node **gc, char *str);
int							setup_heredoc_file(char **filename, t_shell *shell);
char						*find_path_helper(t_shell *s, char **paths,
								char *arg);
/*---------------------------------------------------------------------------*/
t_env						*last_node(t_env *node);
t_env						*find_env_var(t_env *env, char *name);
t_env						*create_node(char *envp, t_gc_node **gc);
/*---------------------------------------------------------------------------*/
t_shell						*get_shell(t_shell *shell);
#endif
