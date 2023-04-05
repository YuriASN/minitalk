NAME = client / server

CC		= gcc
FLAGS	= -Wall -Wextra -Werror
LIBFT	= -Llibft -lft

CLIENT	= client.c
SERVER	= server.c

BCLIENT	= client_bonus.c
BSERVER	= server_bonus.c

HASLIBFT = $(ls -fd libft)

ifeq ($(HASLIBFT), libft)
	LIBFTCLONE = @echo "Found Libft!"
else
	LIBFTCLONE = git clone git@github.com:YuriASN/libft.git
endif


all: $(NAME)

$(NAME):
	$(LIBFTCLONE)
	@make bonus -Clibft/ --no-print-directory
	@$(CC) $(FLAGS) $(CLIENT) $(LIBFT) -o client
	@$(CC) $(FLAGS) $(SERVER) $(LIBFT) -o server
	@echo "\033[95mMinitalk compiled.\033[m"

bonus:

clean:
	@make clean -Clibft/ --no-print-directory
	@/bin/rm -f *.o
	@echo "\033[93mClean done for all.\033[m"

fclean: clean
	@make fclean -Clibft/ --no-print-directory
	@/bin/rm -f server client
	@echo "\033[93mfclean done for all.\033[m"

re: fclean all

restart: fclean
	@/bin/rm -rf libft
	@echo "\033[93mRemoved libft folder.\033[m"
