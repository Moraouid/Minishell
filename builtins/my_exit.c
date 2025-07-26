/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:49:27 by zatais            #+#    #+#             */
/*   Updated: 2025/07/26 09:47:13 by zatais           ###   ########.fr       */
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
	if (status[i] == '-')
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

void	exit_all(int status, t_shell *shell)
{
	// free allocated resources in shell struct
	exit(status);
  // still need update
}

int	my_exit(char **args, t_shell *shell)
{
	int	n;
	int	status;
	int	error;

	if (!shell->cmd->next)
		ft_putendl_fd("exit", 2);
	n = args_counter(args);
	if (!n)
		return (0);
	error = exit_status(args[0], &status);
	if (error)
		return (cmd_error("exit", args[0], "numeric argument required"), 2);
	if (n > 1)
		return (cmd_error("exit", NULL, "too many arguments"), 1);
	if (!shell->cmd->next)
  {
    gc_clean(&shell->gc);
    exit(status);
  }
	return (status);
}

