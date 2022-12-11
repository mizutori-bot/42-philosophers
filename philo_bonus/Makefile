NAME = philo_bonus

SRC = arg_check.c free.c init.c philosophers.c treat_num.c util.c act.c watch.c

SRC_DIR = ./src/
OBJ_DIR = ./obj/
INCLUDES = -I ./include
SRCS = $(addprefix $(SRC_DIR), $(SRC))
OBJS = $(SRC:%.c=$(OBJ_DIR)%.o)
CC = gcc -pthread
FLAG = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAG) $^ $(INCLUDES) -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(FLAG) -c -o $@ $<

clean: 
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean re