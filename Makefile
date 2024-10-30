CC = gcc
FLAGS = -g -Wall -Werror -Wextra
RM = rm -rf

FILES = src/shell.c src/auth.c src/tcp_server.c src/daemon.c
BONUS_FILES = bonus/shell.c bonus/auth.c bonus/tcp_server.c bonus/daemon.c
OBJ_FILES = $(FILES:.c=.o)
BONUS_OBJ_FILE = $(BONUS_FILES:.c=.o)

MSG = Everything is fcleaned!

HEADER = ./src/tcp_server.h
HEADER_BONUS = ./bonus/tcp_server.h
NAME = ft_shield

# UPX packing
UPX = upx
UPX_FLAGS = --best --lzma

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(FLAGS) -o $(NAME)

bonus: $(BONUS_OBJ_FILE)
	$(CC) $(BONUS_OBJ_FILE) $(FLAGS) -o $(NAME)
	$(UPX) $(UPX_FLAGS) $(NAME)

%.o: %.c $(HEADER) $(HEADER_BONUS)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_FILES) $(BONUS_OBJ_FILE)

fclean: clean
	$(RM) $(NAME)
	@echo $(MSG)

re: fclean all

.PHONY: clean fclean re bonus
