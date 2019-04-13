##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

NAME	= 109titration

CC	= gcc


RM	= rm -f

SRCS	= 	109titration.c \
			verification.c

OBJS	= $(SRCS:.c=.o)

CFLAGS = -I ./include

all: $(NAME)

##tests_run:
##				cd tests/ && $(MAKE)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(CFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re tests_run
