NAME = ft_containers

CC = c++

CFLAGS = -Isrc -Wall -Wextra -Werror -std=c++98

SRCS = main.cpp
OBJS = main.o

all: $(NAME)



$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o : %.cpp
	$(CC) $(CFLAGS) -o $@ -c $^

clean:
	rm $(OBJS)

fclean: clean
	rm $(NAME)

re: fclean all