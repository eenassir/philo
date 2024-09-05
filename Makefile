NAME = philo

libft = libft/ft_strlen.c libft/ft_lst_new.c libft/ft_lst_free.c libft/ft_atoi.c libft/ft_strcmp.c

SRC = philo.c philo_utils/get_current_time.c

OBJ = $(SRC:.c=.o) $(libft:.c=.o)

CC = cc

CFLAGS = #-fsanitize=address #-Wall -Wextra -Werror

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