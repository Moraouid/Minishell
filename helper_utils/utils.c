/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:50:14 by zatais            #+#    #+#             */
/*   Updated: 2025/08/11 10:48:14 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

void	cmd_error(char *cmd, char *arg, char *msg, t_gc_node **gc)
{
	char	*str;

	str = ft_strjoin("Niggshell: ", cmd, gc);
	if (arg)
	{
		str = ft_strjoin(str, ": ", gc);
		str = ft_strjoin(str, arg, gc);
	}
	if (msg)
	{
		str = ft_strjoin(str, ": ", gc);
		str = ft_strjoin(str, msg, gc);
	}
	str = ft_strjoin(str, "\n", gc);
	ft_putstr_fd(str, 2);
}

int	is_overflowed(long res, int last_digit, int sign)
{
	long	max_threshold;
	long	min_threshold;
	int		max_last_digit;
	int		min_last_digit;

	max_threshold = LONG_MAX / 10;
	min_threshold = LONG_MIN / 10;
	max_last_digit = 7;
	min_last_digit = -8;
	if (sign == 1 && (res > max_threshold || (res == max_threshold
				&& last_digit > max_last_digit)))
		return (1);
	if (sign == -1 && (-res < min_threshold || (-res == min_threshold
				&& last_digit > -min_last_digit)))
		return (1);
	return (0);
}

long	ft_atol(char *arg, int *overflow)
{
	int		sign;
	long	res;
	int		digit;

	while (is_space(*arg))
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
		if (is_overflowed(res, digit, sign))
			return (*overflow = 1, LONG_MAX);
		res = (res * 10) + digit;
		arg++;
	}
	return (res * sign);
}
