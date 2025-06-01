#include "minishell.h"


//	bdit lik chwya hhhh
void	command_execution(t_read_line *read)
{
	// pwd 
	if (ft_strncmp(read->arg_split[0], "pwd",
			ft_strlen(read->arg_split[0])) == 0 && read->arg_split[1] == NULL)
	{
		read->wcd = getcwd(NULL, 0);
		printf("%s\n", read->wcd);
	}
	// ...
}
