CC = gcc
FLAGS = -g -Wall -Werror -Wextra
RM = rm -rf
UPX = upx
UPX_FLAGS = --best --lzma


NAME = ./mandatory/ft_shield
MANDATORY_HEADER = ./mandatory/ft_shield.h
MANDATORY_FILES = mandatory/service.c \
                 mandatory/daemon.c \
                 mandatory/authentication.c \
                 mandatory/hash.c \
                 mandatory/server.c \
                 mandatory/shell.c \
                 mandatory/quine.c
MANDATORY_MAIN = mandatory/main.c
MANDATORY_OBJ = $(MANDATORY_FILES:.c=.o)

BONUS_NAME = ./bonus/ft_shield
BONUS_HEADER = ./bonus/ft_shield.h
BONUS_FILES = bonus/log_user_action.c \
             bonus/service.c \
             bonus/daemon.c \
             bonus/authentication.c \
             bonus/hash.c \
             bonus/server.c \
             bonus/shell.c \
             bonus/quine.c
BONUS_MAIN = bonus/main.c
BONUS_OBJ = $(BONUS_FILES:.c=.o)


MSG = Everything is fcleaned!

all: $(NAME)


$(NAME): $(MANDATORY_OBJ) $(MANDATORY_MAIN)
	$(CC) $(FLAGS) $(MANDATORY_MAIN) $(MANDATORY_OBJ) -o $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJ) $(BONUS_MAIN)
	$(CC) $(FLAGS) $(BONUS_MAIN) $(BONUS_OBJ) -o $(BONUS_NAME)
	$(UPX) $(UPX_FLAGS) $(BONUS_NAME) 

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(MANDATORY_OBJ)
	$(RM) $(BONUS_OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(BONUS_NAME)
	@echo $(MSG)

re: fclean all

re_bonus: fclean bonus

.PHONY: all bonus clean fclean re re_bonus