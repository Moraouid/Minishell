/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:26:31 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/05/22 03:00:57 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir		*creat_node_red(char *value, char *target, int	type)
{
	t_redir	*t_red;

	t_red = malloc(sizeof(t_red));
	if(!t_red)
		return(NULL);
	t_red->content = value;
	t_red->target = target;
	t_red->type = type;
	t_red->next = NULL;
	return (t_red);
}

t_command	*creat_node_cmd(char **value, t_redir *red)
{
	t_command	*t_cmd;

	t_cmd = malloc(sizeof(t_command));
	if (!t_cmd)
		return (NULL);
	t_cmd->args = value;
	t_cmd->redirs = red;
	t_cmd->next = NULL;
	return (t_cmd);
}

// handel quotes
t_command	*command_line(t_shell *shell)
{
	int i;
	t_redir *red;

	i = 0;
	while(shell->r_line[i])
	{
		if(shell->r_line[i] == '<')
		{
			if(shell->r_line[i] == '<')
			red = creat_node_red("<<", )
		}

	}

}


//	this function for parssing 
void	parsing_command(t_shell *shell)
{
	while (*shell->r_line== ' ')
		shell->r_line++;
	
	// command_execution(read);
}
