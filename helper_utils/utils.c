/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:50:14 by zatais            #+#    #+#             */
/*   Updated: 2025/06/13 21:08:27 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

void	cmd_error(char *cmd, char *arg, char *msg)
{
	write(2, "Niggshell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	if (arg)
	{
		write(2, ": ", 2);
		write(2, arg, ft_strlen(arg));
	}
	if (msg)
	{
		write(2, ": ", 2);
		write(2, msg, ft_strlen(msg));
	}
	write(2, "\n", 1);
}

size_t	ft_atol(char *arg, int *overflow)
{
	int		sign;
	size_t	res;
	int		digit;

	while ((*arg >= 0 && *arg <= 13) || *arg == 32)
		arg++;
	sign = 1;
	if (*arg == '-' || *arg == '+')
	{
		if (*arg == '-')
			sign *= -1;
		arg++;
	}
	res = 0;
	while (*arg >= '0' && *arg <= '9')
	{
		digit = *arg - 48;
		if (res > LONG_MAX)
			return (*overflow = 1, LONG_MAX);
		res = (res * 10) + digit;
		arg++;
	}
	return (res * sign);
}
