NAME = philo

CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread

SRC = 	main.c \
		arguments_check.c \
		ft_mutex.c \
		time.c \
		print.c \
		check.c \
		dinner.c \
		dinner_preparation.c \
		asta.c \

OBJ = $(SRC:.c=.o)

all:$(NAME)

$(NAME): $(OBJ)
	cc $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean:clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
