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

// t_redir		*creat_node_red(char *value, char *target, int	type)
// {
// 	t_redir	*t_red;

// 	t_red = malloc(sizeof(t_red));
// 	if(!t_red)
// 		return(NULL);
// 	t_red->content = value;
// 	t_red->target = target;
// 	t_red->type = type;
// 	t_red->next = NULL;
// 	return (t_red);
// }

void	add_token(t_token **c_line, t_token *new)
{
	t_token	*last;

	if (!new)
		return ;
	if (*c_line == NULL)
	{
		*c_line = new;
		return ;
	}
	last = *c_line;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	new->prev = last;
}

t_token	*creat_node_cmd(char *value, t_type type)
{
	t_token	*t_cmd;

	t_cmd = malloc(sizeof(t_token));
	if (!t_cmd)
		return (NULL);
	t_cmd->cmd = value;
	t_cmd->type = type;
	t_cmd->next = NULL;
	t_cmd->prev = NULL;
	return (t_cmd);
}

void	command_line(t_shell *shell)
{
	int		i;
	int		j;
	char	*cmd;
	t_token	*n_token;

	i = 0;
	while(shell->r_line[i])
	{
		while(shell->r_line[i] == ' ')
			i++;
		if(shell->r_line[i] == '|')
		{
			n_token = creat_node_cmd(ft_strdup("|"), PIPE);
			add_token(&shell->token, n_token);
			i++;
		}
		else if(shell->r_line[i] == '>')
		{
			if(shell->r_line[i + 1] == '>')
			{
				n_token = creat_node_cmd(ft_strdup(">>"), APPEND);
				add_token(&shell->token, n_token);
				i++;
			}
			else
			{
				n_token = creat_node_cmd(ft_strdup(">"), RED_OUT);
				add_token(&shell->token, n_token);
			}
		}
		else if(shell->r_line[i] == '<')
		{
			if(shell->r_line[i + 1] == '<')
			{
				n_token = creat_node_cmd(ft_strdup("<<"), HERDOC);
				add_token(&shell->token, n_token);
				i++;
			}
			else
			{
				n_token = creat_node_cmd(ft_strdup("<"), RED_IN);
				add_token(&shell->token, n_token);
			}
		}
		else
		{
			j = 0;
			while(shell->r_line[i + j] && shell->r_line[i + j] != ' ')
				j++;
			cmd = malloc(j + 1);
			if (!cmd)
				return;
			j = 0;
			while(shell->r_line[i] && shell->r_line[i] != ' ')
				cmd[j++] = shell->r_line[i++];
			cmd[j] = '\0';
			n_token = creat_node_cmd(cmd, WORD);
			add_token(&shell->token, n_token);
		}
		i++;
	}
	t_token *print_tmp = shell->token;
    while(print_tmp != NULL)
    {
        printf("%s\n", print_tmp->cmd);
		if (print_tmp->type == PIPE)
			printf("Type: PIPE\n");
		else if (print_tmp->type == RED_IN)
			printf("Type: RED_IN\n");
		else if (print_tmp->type == RED_OUT)
			printf("Type: RED_OUT\n");
		else if (print_tmp->type == HERDOC)
			printf("Type: HERDOC\n");
		else if (print_tmp->type == APPEND)
			printf("Type: APPEND\n");
		else
			printf("Type: WORD\n");
		printf("------------\n");
        print_tmp = print_tmp->next;
    }
}


//	this function for parssing 
void	parsing_command(t_shell *shell)
{
	command_line(shell);
	// command_execution(read);
}
