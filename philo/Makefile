NAME = philo

utils = utils/ft_strlen.c utils/ft_atoi.c

SRC = philo.c philo_utils/get_current_time.c philo_utils/ft_usleep.c \
philo_utils/ft_monitor.c philo_utils/print_msg.c philo_utils/ft_parcing.c\
philo_utils/ft_num.c philo_utils/ft_loop.c philo_utils/join.c

OBJ = $(SRC:.c=.o) $(utils:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror 

all:$(NAME)

$(NAME):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c /includes/philo.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
