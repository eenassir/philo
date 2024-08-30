NAME = philo

SRC = ft_strlen.c philo.c ft_lst_new.c ft_lst_free.c ft_atoi.c ft_strcmp.c

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -fsanitize=thread #-Wall -Wextra -Werror

all:$(NAME)
$(NAME):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean