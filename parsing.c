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


// handel quotes
char **command_line(char *read_l)
{
	char **cmd = malloc(sizeof(char *) * 100);
	if (!cmd)
		return NULL;
	int i = 0;
	int k = 0;
	int j;
	while (read_l[i])
	{
		while (read_l[i] == ' ')
			i++;
		if (!read_l[i])
			break;
		cmd[k] = malloc(100);
		if (!cmd[k])
			return NULL;
		j = 0;
		if (read_l[i] == '"')
		{
			i++;
			while (read_l[i] && read_l[i] != '"')
				cmd[k][j++] = read_l[i++];
			if (read_l[i] == '"')
				i++;
		}
		else
		{
			while (read_l[i] && read_l[i] != ' ' && read_l[i] != '"')
				cmd[k][j++] = read_l[i++];
		}
		cmd[k][j] = '\0';
		k++;
	}
	cmd[k] = NULL;
	return cmd;
}


//	this function for parssing 
void	parsing_command(t_read_line *read)
{
	if(read->read_line == NULL)
		exit(0);
	if (ft_strlen(read->read_line) == 0)
		return ;
	while (*read->read_line == ' ')
		read->read_line++;
	read->arg_split = command_line(read->read_line);
	// read->arg_split = ft_split(read->read_line, ' ');
	int  i = 0;
	while(read->arg_split[i])
	{
		printf("%s\n", read->arg_split[i]);
		i++;
	}
	command_execution(read);
}
