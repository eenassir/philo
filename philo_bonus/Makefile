NAME = philo_bonus

SRC = philo_bonus.c tphilo_utils/ft_strlen.c tphilo_utils/ft_atoi.c

OBJ = $(SRC:.c=.o)

CC = cc

#CFLAGS = -Wall -Wextra -Werror

all : $(NAME)
$(NAME):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c inlcudes/philo_bonus.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
