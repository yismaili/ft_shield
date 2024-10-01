CC = gcc
FLAGS = -g -Wall -Werror -Wextra
RM = rm -rf

FILES = src/shell.c src/auth.c src/tcp_server.c src/daemon.c
MAIN_FILE = src/main.c src/daemon.c
OBJ_FILES = $(FILES:.c=.o)
MAIN_OBJ_FILE = $(MAIN_FILE:.c=.o)

MSG = Everything is fcleaned!
HEADER = ./src/tcp_server.h
NAME = ./src/ft_shield
MAIN_NAME = shield

all: $(NAME) $(MAIN_OBJ_FILE)

$(NAME): $(OBJ_FILES) $(MAIN_OBJ_FILE)
	$(CC) $(OBJ_FILES) $(FLAGS) -o $(NAME) && $(CC) $(MAIN_OBJ_FILE) $(FLAGS) -o $(MAIN_NAME)
	
%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_FILES) $(MAIN_OBJ_FILE)

fclean: clean
	$(RM) $(NAME) $(MAIN_NAME)
	@echo $(MSG)

re: fclean all

.PHONY: clean fclean re
