/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:49:23 by zatais            #+#    #+#             */
/*   Updated: 2025/07/26 09:58:23 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	my_pwd(t_shell *shell)
{
	char	buff[4096];

	if (!getcwd(buff, sizeof(buff)))
		return (ft_putendl_fd(shell->cwd, 1), 0);
	return (ft_putendl_fd(buff, 1), 0);
}
