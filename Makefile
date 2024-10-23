CC = gcc
FLAGS = -g -Wall -Werror -Wextra
RM = rm -rf

FILES = mandatory/service.c mandatory/daemon.c mandatory/authentication.c mandatory/hash.c mandatory/server.c mandatory/shell.c
MAIN_FILE = mandatory/main.c
OBJ_FILES = $(FILES:.c=.o)
MAIN_OBJ_FILE = $(MAIN_FILE:.c=.o)

MSG = Everything is fcleaned!
HEADER = ./mandatory/ft_shield.h
NAME = ./mandatory/ft_shield
MAIN_NAME = ft_shield

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
