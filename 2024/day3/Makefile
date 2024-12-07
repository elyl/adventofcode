NAME=	day3
SRC=	day3.c
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
