/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:12:49 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/08/03 19:30:37 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

void	shell_init(t_shell *shell)
{
	shell->r_line = NULL;
	shell->tokens = NULL;
	shell->cmd = NULL;
}

// char *get_next_line(int fd)
// {
//     static char buffer[1337];
//     static int pos;
//     static int r;
//     int i = 0;
//     char *line = malloc(100000);

//     if(line == NULL || fd < 0 ||  1337 < 0)
//         return (NULL);
//     while(1)
//     {
//         if(pos >= r)
//         {
//             r = read(fd, buffer, 1337);
//             pos = 0;
//             if(r <= 0)
//                 break ;
//         }
//         if((line[i++] = buffer[pos++]) == '\n')
//             break ;
//     }
//     if(i == 0)
//     {
//         free(line);
//         return (NULL);
//     }
//     return (line);
// }

// size_t	ft_strlcpy(char *dst,  char *src, size_t size)
// {
// 	size_t	i;

// 	i = 0;
// 	if (size != 0)
// 	{
// 		while (src[i] != '\0' && i < size - 1)
// 		{
// 			dst[i] = src[i];
// 			i++;
// 		}
// 		dst[i] = '\0';
// 	}
// 	return (ft_strlen(src));
// }
// static size_t	check_set(char c, char *set)
// {
// 	while (*set)
// 	{
// 		if (*set == c)
// 			return (1);
// 		set++;
// 	}
// 	return (0);
// }

// char	*ft_strtrim(char  *s1, char  *set)
// {
// 	char	*res;
// 	size_t	i;
// 	size_t	size;

// 	if (!s1 || !set)
// 		return (NULL);
// i = 0;
// 	size = ft_strlen(s1);
// 	while (s1[i] && check_set(s1[i], (char *)set))
// 		i++;
// 	while (size > i && check_set(s1[size - 1], (char *)set))
// 		size--;
// 	res = (char *)malloc(size - i + 1);
// 	if (!res)
// 		return (0);
// 	ft_strlcpy(res, s1 + i, size - i + 1);
// 	return (res);
// }
// if (isatty(fileno(stdin)))
// 	shell.r_line = readline("Niggshell~> ");
// else
// {
// 	line = get_next_line(fileno(stdin));
// 	shell.r_line = ft_strtrim(line, "\n");
// 	free(line);
// }

int	shlvl(t_env *env, t_gc_node **gc)
{
	t_env	*sh;
	char	*value;
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

void	init_env(t_env **env, t_gc_node **gc)
{
	char	*a[6];
	char	*pwd;
	char	*p1;
	char	*p2;

	p1 = "PATH=/.local/nvim/bin:/usr/local/sbin:";
	p2 = "/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
	pwd = getcwd(NULL, 0);
	if (!pwd)
		a[0] = ft_strdup("PWD=", gc);
	else
	{
		gc_add(gc, pwd);
		a[0] = ft_strjoin("PWD=", pwd, gc);
	}
	a[1] = ft_strdup("SHLVL=1", gc);
	a[2] = ft_strdup(ft_strjoin(p1, p2, gc), gc);
	a[3] = ft_strdup(ft_strjoin("_=", ft_strjoin(pwd, "/./minishell", gc), gc),
			gc);
	a[4] = ft_strdup("OLDPWD", gc);
	a[5] = NULL;
	my_export(env, a, gc);
}

void	sighandle(int sig)
{
	write(1, "\n", 1);
    rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signals(void)
{
	signal(SIGINT, sighandle);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	shell.env = NULL;
	shell.gc = NULL;
	shell.env_gc = NULL;
	shell.last_exit_status = 0;
	shell.env = NULL;
	if (!copy_env(env, &shell.env, &shell.env_gc))
		init_env(&shell.env, &shell.env_gc);
	else
		shlvl(shell.env, &shell.env_gc);
	while (1337)
	{
		shell_init(&shell);
		setup_signals();
		shell.r_line = readline("Niggshell~> ");
		if (!shell.r_line)
		{
			gc_clean(&shell.gc);
			gc_clean(&shell.env_gc);
			ft_putstr_fd("exit\n", 2);
			exit(shell.last_exit_status);
		}
		gc_add(&shell.gc, shell.r_line);
		if (ft_strlen(shell.r_line))
		{
			add_history(shell.r_line);
			if (parsing_command(&shell))
				start_exec(&shell);
		}
		gc_clean(&shell.gc);
	}
	gc_clean(&shell.env_gc);
}
