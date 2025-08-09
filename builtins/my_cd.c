/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 09:43:25 by zatais            #+#    #+#             */
/*   Updated: 2025/07/26 09:43:25 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_arguments(char **args)
{
	int	count;

	count = 0;
	if (!args)
		return (0);
	while (args[count])
		count++;
	return (count);
}

char	*get_path(t_shell *shell, char **args)
{
	int		count;
	char	*home;
	char	*oldpwd;

	count = count_arguments(args);
	if (count == 0 || !ft_strcmp(args[0], "~"))
	{
		home = get_env_value(shell->env, "HOME");
		if (!home)
			cmd_error("cd", NULL, "HOME not set");
		else if (!*home)
			return (ft_strdup(".", &shell->gc));
		return (home);
	}
	if (!ft_strcmp(args[0], "-"))
	{
		oldpwd = get_env_value(shell->env, "OLDPWD");
		if (!oldpwd)
			cmd_error("cd", NULL, "OLDPWD not set");
		return (oldpwd);
	}
	return (args[0]);
}

void	update_pwd_vars(t_shell *shell, char *oldpwd, char *new)
{
	char	*oldpwd_arg;
	char	*pwd_arg;
	char	*export_args[3];
	char	*unset_arg[2];

	pwd_arg = NULL;
	oldpwd_arg = NULL;
	unset_arg[0] = "OLDPWD";
	unset_arg[1] = NULL;
	if (oldpwd)
	{
		oldpwd_arg = ft_strjoin("OLDPWD=", oldpwd, &shell->gc);
		pwd_arg = ft_strjoin("PWD=", new, &shell->gc);
	}
	else
		my_unset(&shell->env, unset_arg, &shell->gc);
	export_args[0] = oldpwd_arg;
	export_args[1] = pwd_arg;
	export_args[2] = NULL;
	if (oldpwd)
		my_export(&shell->env, export_args, &shell->env_gc);
}

void	update_cwd(t_shell *shell, char *new_path)
{
	char	*new_cwd;

	new_cwd = ft_strdup(new_path, &shell->env_gc);
	shell->cwd = new_cwd;
}

int	my_cd(t_shell *shell, char **args)
{
	char	*oldpwd;
	char	*path;
	int		print;
	char	*new;

	oldpwd = get_env_value(shell->env, "PWD");
	if (count_arguments(args) > 1)
		return (cmd_error("cd", NULL, "too many arguments"), 1);
	path = get_path(shell, args);
	if (!path)
		return (1);
	print = (args[0] && !ft_strcmp(args[0], "-"));
	if (chdir(path))
		return (cmd_error("cd", path, strerror(errno)), 1);
	new = getcwd(NULL, 0);
	if (!new)
	{
		cmd_error("cd",
			"error retrieving current directory: getcwd: cannot access parent directories",
			"No such file or directory");
		new = oldpwd;
	}
	else
		gc_add(&shell->gc, new);
	if (print)
		ft_putendl_fd(new, 1);
	update_pwd_vars(shell, oldpwd, new);
	update_cwd(shell, new);
	return (0);
}
