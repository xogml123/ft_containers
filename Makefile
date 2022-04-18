NAME = ft_containers

CC = c++

CFLAGS = -IsrcS/ -Wall -Wextra -Werror -std=c++98

SRCS = main.cpp
OBJS = main.o

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

bonus: all

%.o : %.cpp
	$(CC) $(CFLAGS)
clean:
	rm -rf $(OBJS)

fclean: clean
	rm $(NAME)

re: fclean all