NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
OBJ = init_bonus.o main_bonus.o routine_bonus.o time_bonus.o death_monitor_bonus.o ft_atoi_bonus.o

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c philo_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean all re fclean
