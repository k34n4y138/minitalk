CC=cc
CFLAGS= -Wall -Werror -Wextra
LIBFT=libft/libft.a
NAME=minitalk

$(NAME):client server


client:client.c $(LIBFT)
	$(CC) $(CFLAGS) client.c -lft -Llibft -o client

server:server.c $(LIBFT)
	$(CC) $(CFLAGS) server.c -lft -Llibft -o server
	
$(LIBFT):
	make -C libft bonus

all: $(NAME)

clean:
	make -C libft fclean

fclean: clean
	rm -rf client server

bonus: $(LIBFT)
	$(CC) $(CFLAGS) client_bonus.c -lft -Llibft -o client
	$(CC) $(CFLAGS) server_bonus.c -lft -Llibft -o server


re: fclean all


.PHONY=all re clean fclean $(NAME) bonus