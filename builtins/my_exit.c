/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:49:27 by zatais            #+#    #+#             */
/*   Updated: 2025/08/11 11:19:45 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exit_status(char *status, int *exit)
{
	long	converted;
	int		overflow;
	int		i;

	overflow = 0;
	i = -1;
	while (is_space(status[++i]))
		;
	if (status[i] == '-' || status[i] == '+')
		++i;
	while (status[i])
	{
		if (!(status[i] >= '0' && status[i] <= '9'))
			return (1);
		i++;
	}
	converted = ft_atol(status, &overflow);
	*exit = converted % 256;
	return (overflow);
}

void	exit_all(int status, t_shell *shell, int count)
{
	if (count == 1)
	{
		close(shell->stdin_fd);
		close(shell->stdout_fd);
	}
	gc_clean(&shell->env_gc);
	gc_clean(&shell->gc);
	exit(status);
}

int	my_exit(char **args, t_shell *shell)
{
	int	n;
	int	status;
	int	error;
	int	cmd_count;

	cmd_count = cmd_counter(shell->cmd);
	n = args_counter(args);
	if (cmd_count == 1)
		ft_putstr_fd("exit\n", 2);
	if (!n)
		exit_all(shell->last_exit_status, shell, cmd_count);
	error = exit_status(args[0], &status);
	if (error)
	{
		cmd_error("exit", args[0], "numeric argument required", &shell->gc);
		exit_all(2, shell, cmd_count);
	}
	if (n > 1)
		return (cmd_error("exit", NULL, "too many arguments", &shell->gc), 1);
	exit_all(status, shell, cmd_count);
	return (status);
}
