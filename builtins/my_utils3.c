/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 06:22:29 by zatais            #+#    #+#             */
/*   Updated: 2025/08/11 11:20:38 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_error2(char *arg)
{
	char	*s;
	t_shell	*shell;

	shell = get_shell(NULL);
	s = ft_strdup("Niggshell: export: `", &shell->gc);
	s = ft_strjoin(s, arg, &shell->gc);
	s = ft_strjoin(s, "': not a valid identifier\n", &shell->gc);
	ft_putstr_fd(s, 2);
}

int	create_new_node(t_env **env, char *arg, t_gc_node **gc)
{
	t_env	*new_node;

	new_node = create_node(arg, gc);
	add_back(env, new_node);
	return (0);
}

int	long_err(char *cmd, t_gc_node **gc)
{
	char	*str;

	str = ft_strdup("error retrieving current directory: ", gc);
	str = ft_strjoin(str, "getcwd: cannot access parent directories ", gc);
	cmd_error(cmd, str, "No such file or directory", gc);
	return (0);
}
