NAME		=	ft_containers
CC			=	c++
FLAGS		=	-Wall -Wextra -Werror -std=c++98

SRCS		=	main.cpp
				
OBJS	=	$(SRCS:.cpp=.o)

%.o		:	%.cpp
			$(CC) $(FLAGS) -o $@ -c $<
all		: 	$(NAME)

$(NAME)	:	$(OBJS)
			$(CC) -o $(NAME) $(FLAGS) $(OBJS)

clean	:	
				rm $(OBJS)

fclean	:	clean
				rm -rf $(NAME)

re		:	fclean all


.PHONY	:	all clean fclean re
