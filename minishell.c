/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:12:49 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/08/10 21:09:32 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	shlvl(t_env *env, t_gc_node **gc)
{
	char	*value;
	t_env	*sh;
	int		n;
	int		ovf;

	sh = find_env_var(env, "SHLVL");
	if (!sh)
		return (0);
	value = ft_strchr(sh->value, '=') + 1;
	n = ft_atol(value, &ovf);
	n += 1;
	sh->value = ft_strjoin("SHLVL=", ft_itoa(n, gc), gc);
	return (1);
}

void	init_env(t_shell *shell, t_env **env, t_gc_node **gc)
{
	char	*a[5];
	char	*pwd;
	char	*str;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		a[0] = ft_strdup("PWD=", gc);
	else
	{
		gc_add(gc, pwd);
		shell->cwd = pwd;
		a[0] = ft_strjoin("PWD=", pwd, gc);
	}
	a[1] = ft_strdup("SHLVL=1", gc);
	str = ft_strjoin("_=", ft_strjoin(pwd, "/./minishell", gc), gc);
	a[2] = str;
	a[3] = ft_strdup("OLDPWD", gc);
	a[4] = NULL;
	my_export(env, a, gc);
}

void	initialize_shell(t_shell *shell, char **env)
{
	char	*pwd;

	memset(shell, 0, sizeof(t_shell));
	if (!env || !*env)
		init_env(shell, &shell->env, &shell->env_gc);
	else
		copy_env(env, &shell->env, &shell->env_gc);
	shlvl(shell->env, &shell->env_gc);
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		long_err("pwd", &shell->gc);
		long_err("pwd", &shell->gc);
		shell->cwd = NULL;
	}
	else
	{
		shell->cwd = pwd;
		gc_add(&shell->env_gc, pwd);
	}
	shell->herdoc_fd = -1;
	get_shell(shell);
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	initialize_shell(&shell, env);
	while (1337)
	{
		get_signal_index(0);
		setup_signals();
		shell.r_line = readline("Niggshell~> ");
		if (!shell.r_line)
		{
			ft_putstr_fd("exit\n", 2);
			break ;
		}
		if (ft_strlen(shell.r_line))
		{
			add_history(shell.r_line);
			gc_add(&shell.gc, shell.r_line);
			if (parsing_command(&shell))
				start_exec(&shell);
		}
		gc_clean(&shell.gc);
	}
	clean_exit(shell.last_exit_status, &shell);
}
