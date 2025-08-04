/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:49:17 by zatais            #+#    #+#             */
/*   Updated: 2025/06/19 18:14:53 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_args(char **args, int flag, int start, int spaces)
{
	while (args[start])
	{
		ft_putstr_fd(args[start], 1);
		if (spaces-- > 0)
			write(1, " ", 1);
		start++;
	}
	if (!flag)
		write(1, "\n", 1);
}

int	check_flag(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '-')
		return (0);
	++i;
	while (arg[i] && arg[i] == 'n')
		i++;
	if (!arg[i])
		return (1);
	return (0);
}

int	args_counter(char **args)
{
	int	count;

	count = -1;
	while (args[++count])
		;
	return (count);
}

int	my_echo(char **args)
{
	int	i;
	int	flag;
	int	spaces;

	i = -1;
	flag = 0;
	while (args[++i] && check_flag(args[i]))
		flag = 1;
	spaces = args_counter(args) - i - 1;
	print_args(args, flag, i, spaces);
	return (0);
}
