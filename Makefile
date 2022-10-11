CC :=	gcc
SRCS :=	get_next_line.c get_next_line_utils.c
OBJ :=	$(SRCS:.c=.o)
RM :=	rm -f
CFLAGS :=	-Wall -Werror -Wextra
NAME :=	get_next_line.a
AR :=	ar -rs

all:	$(NAME)

$(NAME):	$(OBJ)
		$(AR) $(NAME) $^

clean:
		$(RM) $(OBJ) $(BNSOBJ)

fclean: clean
		$(RM) $(NAME)

re:	fclean all