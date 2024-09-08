CC = gcc
FLAGS = -g -Wall -Werror -Wextra #-g -fsanitize=address
RM = rm -rf

FILES = src/shell.c src/auth.c src/tcp_server.c src/daemon.c
OBJ_FILES = $(FILES:.c=.o)

MSG = Everything is fcleaned!
HEADER = ./src/tcp_server.h
NAME = ft_shield

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(FLAGS) -o $(NAME)
	
%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_FILES)

fclean: clean
	$(RM) $(NAME)
	@echo $(MSG)

re: fclean all

.PHONY: clean fclean re
