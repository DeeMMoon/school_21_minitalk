CLIENT	= client
SERVER = server
SRCS_CLIENT = client.c
SRCS_SERVER = server.c
OBJS_CLIENT	= $(SRCS_CLIENT:.c=.o)
OBJS_SERVER	= $(SRCS_SERVER:.c=.o)

CLIENT_B = client_bonus
SERVER_B = server_bonus
SRCS_CLIENT_B = client_bonus.c
SRCS_SERVER_B = server_bonus.c
OBJS_CLIENT_B	= $(SRCS_CLIENT_B:.c=.o)
OBJS_SERVER_B	= $(SRCS_SERVER_B:.c=.o)

CC			= gcc

CFLAGS		= -Wall -Werror -Wextra

.c.o:		$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all:		$(SERVER) $(CLIENT)

$(CLIENT):	$(OBJS_CLIENT) Makefile
				$(CC) $(CFLAGS) $(OBJS_CLIENT) -o client

$(SERVER):	$(OBJS_SERVER) Makefile
				$(CC) $(CFLAGS) $(OBJS_SERVER) -o server

bonus:		$(SERVER_B) $(CLIENT_B)

$(CLIENT_B):	$(OBJS_CLIENT_B) Makefile
				$(CC) $(CFLAGS) $(OBJS_CLIENT_B) -o client

$(SERVER_B):	$(OBJS_SERVER_B) Makefile
				$(CC) $(CFLAGS) $(OBJS_SERVER_B) -o server

clean:
			rm -f $(OBJS_CLIENT) $(OBJS_SERVER)
			rm -f $(OBJS_CLIENT_B) $(OBJS_SERVER_B)

fclean:		clean
			rm -f $(CLIENT) $(SERVER)
			rm -f $(CLIENT_B) $(SERVER_B)

re:			fclean all

.PHONY:		all clean fclean bonus re
