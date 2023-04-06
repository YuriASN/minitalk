NAME = client / server

CC		= gcc
FLAGS	= -Wall -Wextra -Werror
LIBFT	= -Llibft -lft

CLIENT	= client.c
SERVER	= server.c

BCLIENT	= client_bonus.c
BSERVER	= server_bonus.c


all: $(NAME)

$(NAME):
	@make bonus -Clibft/ --no-print-directory
	@$(CC) $(FLAGS) $(CLIENT) $(LIBFT) -o client
	@$(CC) $(FLAGS) $(SERVER) $(LIBFT) -o server
	@echo "\033[95mMinitalk compiled.\033[m"

bonus:
	@make bonus -Clibft/ --no-print-directory
	@$(CC) $(FLAGS) $(BCLIENT) $(LIBFT) -o client
	@$(CC) $(FLAGS) $(BSERVER) $(LIBFT) -o server
	@echo "\033[95mMinitalk bonus compiled.\033[m"
clean:
	@make clean -Clibft/ --no-print-directory
	@/bin/rm -f *.o
	@echo "\033[93mClean done for all.\033[m"

fclean: clean
	@make fclean -Clibft/ --no-print-directory
	@/bin/rm -f server client server_bonus client_bonus
	@echo "\033[93mfclean done for all.\033[m"

re: fclean all

rebonus: fclean bonus