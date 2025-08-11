/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:49:23 by zatais            #+#    #+#             */
/*   Updated: 2025/08/10 21:01:51 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	my_pwd(t_shell *shell)
{
	char	buff[4096];

	if (!getcwd(buff, sizeof(buff)))
	{
		if (!shell->cwd)
			return (long_err("pwd", &shell->gc));
		return (ft_putendl_fd(shell->cwd, 1), 0);
	}
	return (ft_putendl_fd(buff, 1), 0);
}
