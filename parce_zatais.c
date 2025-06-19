int is_space(char c)
{
  return ((c >= 0 && c <= 13) || c == 32);
}

t_token_type	identify_separator(char *str, int i)
{
	if (str[i] == '|')
		return (PIPE);
	if (str[i] == '<')
	{
		if (str[i + 1] == '<')
			return (HEREDOC);
		return (INPUT);
	}
	if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			return (APPEND);
		return (OUTPUT);
	}
	if (is_space(str[i]))
		return (SPACES);
	if (str[i] == '\0')
		return (END);
	return (0);
}

int	update_quote_status(int status, char c)
{
	if (c == '\'' && status == DEFAULT)
		return (SQUOTE);
	if (c == '\"' && status == DEFAULT)
		return (DQUOTE);
	if (c == '\'' && status == SQUOTE)
		return (DEFAULT);
	if (c == '\"' && status == DQUOTE)
		return (DEFAULT);
	return (status);
}

void	add_token(t_shell *shell, t_token_type type, char *value)
{
	t_token	*new_token;
	t_token	*current;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->value = value;
	new_token->type = type;
	new_token->next = NULL;
	if (!shell->tokens)
	{
		shell->tokens = new_token;
		return ;
	}
	current = shell->tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

char	*ft_substr2(char *str, int start, int end)
{
	int		len;
	char	*res;
	int		i;

	len = end - start;
	if (len <= 0)
		return (NULL);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = -1;
	while (++i < len)
		res[i] = str[start + i];
	res[len] = '\0';
	return (res);
}

int save_word_token(t_shell *shell, char *str, int start, int end)
{
	char	*value;

	value = ft_substr2(str, start, end);
  if (!value)
    return(0);
	return (add_token(shell, WORD, value), 1);
}

int	save_operator_token(t_shell *shell, char *str, int index,
		t_token_type type)
{
	char	*value;

	if (type == HEREDOC || type == APPEND)
		value = ft_substr2(str, index, index + 2);
	else
		value = ft_substr2(str, index, index + 1);
  if (!value)
    return (0);
  return (add_token(shell, type, value), 1);
}

int	process_character(t_shell *shell, char *str, int *index, int token_start)
{
	t_token_type	type;

	type = identify_separator(str, *index);
	if (type && *index != token_start)
		if (!save_word_token(shell, str, token_start, *index))
      return(-1);
	if (type == PIPE || type == INPUT || type == OUTPUT || type == HEREDOC
		|| type == APPEND)
	{
		if(!save_operator_token(shell, str, *index, type))
      return (-1);
		if (type == HEREDOC || type == APPEND)
			return (*index += 1, *index + 1);
	}
	if (type)
		return (*index + 1);
	return (token_start);
}

void	print_error(char *msg1, char *msg2, int specific)
{
	if (specific)
		printf("Error: %s '%s'\n", msg1, msg2);
	else
		printf("Error: %s %s\n", msg1, msg2);
}

void	handle_quote_error(int status)
{
	if (status == SQUOTE)
		print_error("unexpected EOF while looking for matching", "\'", 1);
	else if (status == DQUOTE)
		print_error("unexpected EOF while looking for matching", "\"", 1);
	print_error("syntax error", "unexpected end of file", 0);
}

int	tokenize_input(t_shell *shell, char *input)
{
	int	i;
	int	token_start;
	int	status;
	int	length;

	i = -1;
	token_start = 0;
	status = DEFAULT;
	length = ft_strlen(input);
	while (++i <= length)
	{
    //check if you are inside quotes 
		status = update_quote_status(status, input[i]);
    // only enter if you are outside quotes 
		if (status == DEFAULT)
			token_start = process_character(shell, input, &i, token_start); // check if you are in a separator "| ,> ,>> ,< ,<< ,space ,'\0' " start copying from the first char of the the word that start point to then move the start to the next word
    // example : hello>world\0
    //           ^    ^^     ^→sep →start copying from start index 
    //                 →start point here now
    //        start  sep
    //           i→→→→ start copying frome the start and mov start to the next word 
      if (token_start == -1)
        return(0);
	}
	if (status != DEFAULT)
		return (handle_quote_error(status), 0);
	return (1);
}

void	print_tokens(t_shell *shell)
{
	t_token	*current;
	char	*type_str;
	char	*val;
	char	display[256];
	int		pos;

	current = shell->tokens;
	printf("\nTokens:\n-----------------\n");
	while (current)
	{
		if (current->type == WORD)
			type_str = "WORD";
		else if (current->type == PIPE)
			type_str = "PIPE";
		else if (current->type == INPUT)
			type_str = "INPUT";
		else if (current->type == OUTPUT)
			type_str = "OUTPUT";
		else if (current->type == HEREDOC)
			type_str = "HEREDOC";
		else if (current->type == APPEND)
			type_str = "APPEND";
		else if (current->type == SPACES)
			type_str = "SPACES";
		val = current->value;
		pos = 0;
		while (*val)
		{
			if (*val == '\"')
			{
				display[pos] = '\\';
				pos++;
				display[pos] = '\"';
			}
			else if (*val == '\'')
			{
				display[pos] = '\\';
				pos++;
				display[pos] = '\'';
			}
			else
			{
				display[pos] = *val;
			}
			pos++;
			val++;
		}
		display[pos] = '\0';
		printf("[%-6s] = '%s'\n", type_str, display);
		current = current->next;
	}
	printf("-----------------\n");
}

void	free_tokens(t_shell *shell)
{
	t_token	*current;
	t_token	*next;

	current = shell->tokens;
	while (current)
	{
		next = current->next;
		free(current->value);// strdup
		free(current);
		current = next;
	}
	shell->tokens = NULL;
}
