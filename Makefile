CC=cc
CFLAGS= -Wall -Werror -Wextra
LIBFT=libft/libft.a

CLNT_EXEC=client
CLNT_SRCS=client.c
CLNT_HDRS=client.h

SVR_EXEC=server
SVR_SRCS=sever.c
SVR_HDRS=server.h

NAME=minitalk

$(NAME):client server


client:client.c client.h $(HDRS) $(LIBFT)
	$(CC) $(CFLAGS) client.c -lft -Llibft -o client

server:server.c server.h $(HDRS) $(LIBFT)
	$(CC) $(CFLAGS) server.c -lft -Llibft -o server
	
$(LIBFT):
	make -C libft

all: $(NAME)

clean:
	make -C libft fclean

fclean: clean
	rm -rf $(CLNT_EXEC) $(SVR_EXEC)

bonus: $(LIBFT)
	$(CC) $(CFLAGS) client_bonus.c -lft -Llibft -o client
	$(CC) $(CFLAGS) server_bonus.c -lft -Llibft -o server


re: fclean all


.PHONY=all re clean fclean $(NAME) bonus