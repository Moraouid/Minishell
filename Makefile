NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
INCLUDE = -I/usr/include/readline -lreadline $(LIBFT) 
SRC = minishell.c parsing.c excution.c
OBJS = $(SRC:.c=.o)

all: $(NAME)
# add relink rule for the header
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(INCLUDE)

$(LIBFT):
	make -C libft

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all
