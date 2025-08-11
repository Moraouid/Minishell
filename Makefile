SRCS = minishell.c \
	builtins/my_cd.c \
	builtins/my_echo.c \
	builtins/my_env.c \
	builtins/my_exit.c \
	builtins/my_export.c \
	builtins/my_pwd.c \
	builtins/my_unset.c \
	builtins/my_utils.c \
	builtins/my_utils2.c \
	builtins/my_utils3.c \
	exec/exec.c \
	exec/exec_utils.c \
	exec/exec_utils2.c \
	exec/exec_utils3.c \
	exec/redirect_utils.c \
	helper_utils/copy_env.c \
	helper_utils/ft_split.c \
	helper_utils/gc.c \
	helper_utils/utils.c \
	helper_utils/utils2.c \
	helper_utils/utils3.c \
	helper_utils/utils4.c \
	herdoc/heredoc.c \
	herdoc/heredoc_utils.c \
	herdoc/heredoc_utils2.c \
	parse/creat_command.c \
	parse/parsing.c \
	parse/parsing_utils.c \
	parse/syntax_errors.c \
	parse/expansions/expand_help.c \
	parse/expansions/expand_utils.c \
	parse/expansions/expansions.c \
	parse/expansions/split_after_expand.c \
	parse/remove_quotes/remove_expand_quotes.c \
	parse/remove_quotes/remove_quotes.c \
	parse/tokeniziation/tokeniziation.c \
	parse/tokeniziation/tokeniziation_help.c \
	signal/signal.c

OBJS = $(SRCS:.c=.o)
NAME = minishell
CC = cc 
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline
INCLUDES = -I/usr/include/readline

all: $(NAME)
	@clear
	@echo "                                                                        "
	@echo "███╗   ██╗██╗ ██████╗  ██████╗ ███████╗██╗  ██╗███████╗██╗     ██╗"     
	@echo "████╗  ██║██║██╔════╝ ██╔════╝ ██╔════╝██║  ██║██╔════╝██║     ██║"     
	@echo "██╔██╗ ██║██║██║  ███╗██║  ███╗███████╗███████║█████╗  ██║     ██║"     
	@echo "██║╚██╗██║██║██║   ██║██║   ██║╚════██║██╔══██║██╔══╝  ██║     ██║"     
	@echo "██║ ╚████║██║╚██████╔╝╚██████╔╝███████║██║  ██║███████╗███████╗███████╗"
	@echo "╚═╝  ╚═══╝╚═╝ ╚═════╝  ╚═════╝ ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"
	@echo "                        Welcome to Niggshell"
	@echo

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

%.o: %.c includes/exec.h includes/parse.h includes/minishell.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
