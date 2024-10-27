NAME = ./mandatory/ft_shield

CC = gcc
FLAGS = -g -Wall -Werror -Wextra
RM = rm -rf

FILES = mandatory/service.c mandatory/daemon.c mandatory/authentication.c mandatory/hash.c mandatory/server.c mandatory/shell.c mandatory/quine.c
MAIN_FILE = mandatory/main.c
OBJ_FILES = $(FILES:.c=.o)

MSG = Everything is fcleaned!
HEADER = ./mandatory/ft_shield.h

all: $(NAME)

$(NAME): $(MAIN_FILE) $(HEADER) $(OBJ_FILES)
	$(CC) $(FLAGS) $(MAIN_FILE) $(OBJ_FILES) -o $(NAME)
	
%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) -f $(OBJ_FILES)

fclean: clean
	$(RM) $(NAME)
	@echo $(MSG)

re: fclean all

.PHONY:  all clean fclean re
