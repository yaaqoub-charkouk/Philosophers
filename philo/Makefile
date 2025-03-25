NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror  #-fsanitize=thread -g
OBJ = utils/clean.o utils/ft_atoi.o init.o main.o routine_actions.o routine.o time.o death_monitor.o 

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o:%.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean all re fclean
