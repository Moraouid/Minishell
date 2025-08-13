/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 11:20:15 by zatais            #+#    #+#             */
/*   Updated: 2025/08/12 23:26:37 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**convert_env(t_shell *shell, t_gc_node **gc)
{
	int		i;
	int		count;
	char	**envp;
	t_env	*tmp;

	count = 0;
	tmp = shell->env;
	while (tmp)
	{
		++count;
		tmp = tmp->next;
	}
	envp = gc_malloc(gc, (count + 1) * sizeof(char *));
	tmp = shell->env;
	i = -1;
	while (tmp)
	{
		envp[++i] = tmp->value;
		tmp = tmp->next;
	}
	envp[count] = NULL;
	return (envp);
}

char	*find_bin(t_shell *s, char *arg, t_env *env, int *err)
{
	char	**paths;
	char	*path;

	if (!ft_strncmp(arg, "..", 3) || !ft_strncmp(arg, ".", 2))
		return (s->cmd_perm = 0, NULL);
	path = get_env_value(env, "PATH");
	if (!path || !*path)
		return (s->cmd_perm = 0, *err = 1, NULL);
	paths = ft_split(path, ':', &s->gc);
	return (find_path_helper(s, paths, arg));
}

void	check_dir(t_shell *shell, t_command *cur_cmd)
{
	struct stat	statbuf;

	if (stat(cur_cmd->args[0], &statbuf))
	{
		cmd_error(cur_cmd->args[0], NULL, strerror(errno), &shell->gc);
		if (errno == ENOENT)
			clean_exit(127, shell);
		else
			clean_exit(126, shell);
	}
	if (S_ISDIR(statbuf.st_mode))
	{
		cmd_error(cur_cmd->args[0], NULL, "is a directory", &shell->gc);
		clean_exit(126, shell);
	}
}

void	is_not_found(t_shell *sh, t_command *cur_cmd, char **full_path)
{
	int	err;

	err = 0;
	sh->cmd_perm = 1;
	if (!*cur_cmd->args[0])
	{
		cmd_error(cur_cmd->args[0], NULL, "command not found", &sh->gc);
		clean_exit(127, sh);
	}
	if (ft_strchr(cur_cmd->args[0], '/'))
	{
		check_dir(sh, cur_cmd);
		*full_path = cur_cmd->args[0];
	}
	else
		*full_path = find_bin(sh, cur_cmd->args[0], sh->env, &err);
	if (!*full_path && !sh->cmd_perm)
	{
		if (!err)
			cmd_error(cur_cmd->args[0], NULL, "command not found", &sh->gc);
		else
			cmd_error(cur_cmd->args[0], NULL, "No such file or directory",
				&sh->gc);
		clean_exit(127, sh);
	}
}

void	check_perm(char *full_path, t_shell *shell)
{
	if (access(full_path, X_OK))
	{
		cmd_error(full_path, NULL, "permission denied", &shell->gc);
		clean_exit(126, shell);
	}
}
