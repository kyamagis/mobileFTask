CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address

INCLUDE = -I$(TASK_HEADERS) 
SRCS = ./src/main.c\


OBJS = $(SRCS:.c=.o)
NAME = hastime

TASK_HEADERS = ./include/

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: all
	bash test.sh

.PHONY: all clean fclean re test