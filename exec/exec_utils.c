/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 11:20:15 by zatais            #+#    #+#             */
/*   Updated: 2025/08/03 11:20:15 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**convert_env(t_shell *shell, t_gc_node **gc)
{
	int		count;
	t_env	*tmp;
	char	**envp;
	int		i;

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

char	*find_bin(t_shell *shell, char *arg, t_env *env)
{
	char	*full_path;
	char	**paths;
	char	*path;
	int		i;

	if (!ft_strncmp(arg, "..", 3) || !ft_strncmp(arg, ".", 2))
		return (NULL);
	path = get_env_value(env, "PATH"); //
	if (!path || !*path)
		path = ft_strdup(shell->cwd, &shell->gc);
	paths = ft_split(path, ':', &shell->gc);
	i = -1;
	while (paths[++i])
	{
		full_path = ft_strjoin(ft_strjoin(paths[i], "/", &shell->gc), arg,
				&shell->gc);
		if (!access(full_path, F_OK))
			return (full_path);
	}
	return (NULL);
}
/*in case of unset PATH and unset PATH
tmp_x_file1 --> permission dinied shoulld appear
echo $?*/
int	is_not_found(t_shell *shell, t_command *cur_cmd, char **full_path)
{
	struct stat	statbuf;

	if (!*cur_cmd->args[0])
	{
		cmd_error(cur_cmd->args[0], NULL, "command not found");
		return (1);
	}
	if (ft_strchr(cur_cmd->args[0], '/'))
	{
		if (stat(cur_cmd->args[0], &statbuf))
		{
			cmd_error(cur_cmd->args[0], NULL, strerror(errno));
			if (errno == ENOENT)
				clean_exit(127, shell);
			else
				clean_exit(126, shell);
		}
		if (S_ISDIR(statbuf.st_mode))
		{
			cmd_error(*full_path, NULL, "is a directory");
			clean_exit(126, shell);
		}
		*full_path = ft_strdup(cur_cmd->args[0], &shell->gc);
	}
	else
		*full_path = find_bin(shell, cur_cmd->args[0], shell->env);
	if (!*full_path || access(*full_path, F_OK))
	{
		cmd_error(cur_cmd->args[0], NULL, "command not found");
		return (1);
	}
	return (0);
}


int	check_perm(char *full_path, t_shell *shell)
{
	if (access(full_path, X_OK))
	{
		cmd_error(full_path, NULL, "permission denied");
		gc_clean(&shell->gc);
		gc_clean(&shell->env_gc);
		return (1);
	}
	return (0);
}
