CC= cc

CFLAGS= -Wall -Werror -Wextra

SRC= get_next_line.c get_next_line_utils.c

OBJ= $(SRC:.c=.o)

NAME= get_next_line

RM= rm -f

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re