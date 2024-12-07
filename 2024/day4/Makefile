NAME=	day4
SRC=	day4.c	\
	get_next_line.c
OBJ=	$(SRC:.c=.o)
CC=	gcc
CFLAGS=	-W -Wall -ansi -pedantic -g

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -fv $(OBJ)

fclean:
	rm -fv $(NAME)

re:	clean fclean $(NAME)
