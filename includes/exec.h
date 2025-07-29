/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 08:00:31 by zatais            #+#    #+#             */
/*   Updated: 2025/07/26 08:23:14 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_shell		t_shell;
typedef struct s_env		t_env;
typedef struct s_gc_node	t_gc_node;
typedef struct s_redir      t_redir;
typedef struct s_command	t_command;

//??
size_t						ft_strlen(char *s);
void						ft_putstr_fd(char *s, int fd);
int							my_echo(char **args);
void						ft_putendl_fd(char *s, int fd);
void						cmd_error(char *cmd_name, char *error_arg,
								char *error_msg);
int							args_counter(char **args);
long						ft_atol(char *arg, int *overflow);
int							is_space(char c);
int							ft_strncmp(char *s1, char *s2, size_t n);
int							copy_env(char **envp, t_env **env, t_gc_node **gc);
t_env						*last_node(t_env *node);
void						add_back(t_env **env, t_env *new);
int							my_echo(char **args);
int							my_pwd(t_shell *shell);
int							my_exit(char **args, t_shell *shell);
int							my_unset(t_env **env, char **args, t_gc_node **gc);
int							is_var_exist(t_env *env, char *var);
int							ft_strcmp(char *s1, char *s2);
char						*ft_strndup(char *s, size_t n, t_gc_node **gc);
char						*ft_strchr(char *s, int c);
int							ft_isalnum(int c);
int							ft_isalpha(int c);
int							my_env(t_env *env, char **args);
t_env						*find_env_var(t_env *env, char *name);
int							my_cd(t_shell *shell, char **args, t_gc_node **gc);
char						**ft_split(char *s, char c, t_gc_node **gc);
int							my_export(t_env **env, char **args, t_gc_node **gc);
char						*ft_strdup(char *s, t_gc_node **gc);
void						*gc_malloc(t_gc_node **gc, size_t size);
void						gc_clean(t_gc_node **gc);
void						gc_remove(t_gc_node **gc, void *ptr);
void						gc_add(t_gc_node **gc, void *ptr);
char						*ft_strjoin(char *s1, char *s2, t_gc_node **gc);
t_env						*create_node(char *envp, t_gc_node **gc);
void						start_exec(t_shell *shell);
char						*get_env_value(t_env *env, char *key);
int							cmd_counter(t_command *cmd);
void						restore_stds(int stdin, int stdout);
int							redirect(t_redir *rd);
int							open_in(int *fd, char *filename);
int							is_not_found(t_shell *shell, t_command *cur_cmd,
								char **full_path);

char						**convert_env(t_shell *shell, t_gc_node **gc);
char						*find_bin(char *arg, t_env *env, t_gc_node **gc,
								int *f_err);
int							is_dir(char *full_path);
int							dir_perm(char *full_path, t_shell *shell);
void	exec_child(t_shell *shell, t_command *cur_cmd);
int	is_builtin(char *cmd);
int	execute_builtin(t_shell *shell, t_command *cmd);
#endif
