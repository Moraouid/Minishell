/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:49:23 by zatais            #+#    #+#             */
/*   Updated: 2025/08/03 19:14:41 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	my_pwd(t_shell *shell)
{
	char	buff[4096];

	if (!getcwd(buff, sizeof(buff)))
	{
		if (!shell->cwd)
		{
			cmd_error("pwd",
				"error retrieving current directory: getcwd: cannot access parent directories: ",
				"No such file or directory");
			return (0);
		}
		return (ft_putendl_fd(shell->cwd, 1), 0);
	}
	return (ft_putendl_fd(buff, 1), 0);
}
