NAME = philo

SRC = util.c util2.c philosophers.c free.c init_philos.c act.c watch_philos.c num_treat.c arg_check.c

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

.PHONY: all clean re fclean