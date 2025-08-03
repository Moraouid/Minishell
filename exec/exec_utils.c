



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

char	*find_bin(char *arg, t_env *env, t_gc_node **gc, int *f_err)
{
	char	*full_path;
	char	**paths;
	char	*path;
	int		i;

	path = get_env_value(env, "PATH");
	if (!path || !*path)
	{
		*f_err = 1;
		return (NULL);
	}
	paths = ft_split(path, ':', gc);
	i = -1;
	while (paths[++i])
	{
		full_path = ft_strjoin(ft_strjoin(paths[i], "/", gc), arg, gc);
		if (!access(full_path, F_OK))
			return (full_path);
	}
	return (NULL);
}

int	is_not_found(t_shell *shell, t_command *cur_cmd, char **full_path)
{
	int	err;

	err = 0;
	if (!*cur_cmd->args[0])
	{
		cmd_error(cur_cmd->args[0], NULL, "command not found");
		gc_clean(&shell->gc);
		gc_clean(&shell->env_gc);
		return (1);
	}
	if (ft_strchr(cur_cmd->args[0], '/'))
    {
		*full_path = ft_strdup(cur_cmd->args[0], &shell->gc);
        err = 1;
    }
	else
		*full_path = find_bin(cur_cmd->args[0], shell->env, &shell->gc, &err);
	if (!*full_path || access(*full_path, F_OK))
	{
		if (!err)
			cmd_error(cur_cmd->args[0], NULL, "command not found");
		else
			cmd_error(cur_cmd->args[0], NULL, "No such file or directory");
		gc_clean(&shell->gc);
        gc_clean(&shell->env_gc);
		return (1);
	}
	return (0);
}

int	is_dir(char *full_path)
{
	struct stat	statbuf;

	if (!stat(full_path, &statbuf))
		return (S_ISDIR(statbuf.st_mode));
	return (0);
}

int	dir_perm(char *full_path, t_shell *shell)
{
	if (is_dir(full_path))
	{
		cmd_error(full_path, NULL, "is a directory");
		gc_clean(&shell->gc);
        gc_clean(&shell->env_gc);
        return (1);
	}
    //shoild tragger this error |^
	if (access(full_path, X_OK))
	{
		cmd_error(full_path, NULL, "permission denied");
		gc_clean(&shell->gc);
        gc_clean(&shell->env_gc);
		return (1);
	}
	return (0);
}


