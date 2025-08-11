/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:49:17 by zatais            #+#    #+#             */
/*   Updated: 2025/08/11 10:47:49 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_args(char **args, int flag, int start, int spaces)
{
	char	*s;
	t_shell	*shell;

	shell = get_shell(NULL);
	s = ft_strdup("", &shell->gc);
	while (args[start])
	{
		s = ft_strjoin(s, args[start], &shell->gc);
		if (spaces-- > 0)
			s = ft_strjoin(s, " ", &shell->gc);
		start++;
	}
	if (!flag)
		s = ft_strjoin(s, "\n", &shell->gc);
	ft_putstr_fd(s, 1);
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
