/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:14:06 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/05/22 23:17:58 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_read_line
{
	char	*read_line;
	char	*wcd;
	char	**arg_split;
}			t_read_line;


/* parsing_command */
void		parsing_command(t_read_line *read_line);

/* execution */
void		command_execution(t_read_line *read);

#endif