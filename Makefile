NAME = philo

utils = utils/ft_strlen.c utils/ft_lst_new.c utils/ft_lst_free.c utils/ft_atoi.c utils/ft_strcmp.c

SRC = philo.c philo_utils/get_current_time.c

OBJ = $(SRC:.c=.o) $(utils:.c=.o)

CC = cc

# CFLAGS = -fsanitize=thread -g

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
