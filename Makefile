NAME		=	ft_containers
CC			=	c++
FLAGS		=	-Wall -Wextra -Werror -std=c++98

SRC_MAIN		=	main.cpp

SRCS_CONTAINER	=	vector.cpp \
					map.cpp \
					stack.cpp

SRCS_ETC	=	allocator.cpp \
				pair.cpp

SRCS_ITERATOR	=	vector_iterator.cpp \
					vector_rev_iterator.cpp \
					map_iterator.cpp \
					map_rev_iterator.cpp

DIR_CONTAINER	=	container/
DIR_ETC	=	etc/
DIR_ITERATOR	=	iterator/

INCLUDES	=	-I $(DIR_CONTAINER) -I $(DIR_ETC) -I $(DIR_ITERATOR)
				
OBJS_MAIN		=	$(SRCS_MAIN:.cpp=.o)
OBJS_CONTAINER	=	$(SRCS_CONTAINER:.cpp=.o)
OBJS_ETC	=	$(SRCS_ETC:.cpp=.o)
OBJS_ITERATOR	=	$(SRCS_ITERATOR:.cpp=.o)


all		: 	$(NAME)

$(NAME)	:	$(OBJS)
			$(CC) -o $(NAME) $(FLAGS) $(OBJS)

$(OBJS)	:	$(addprefix $(DIR_CONTAINER), $(OBJS_CONTAINER)) $(addprefix $(DIR_ETC), $(OBJS_ETC)) \
			$(addprefix $(DIR_ITERATOR), $(OBJS_ITERATOR))

clean	:	
				rm $(OBJS)

fclean	:	clean
				rm -rf $(NAME)

re		:	fclean all

%.o		:	%.cpp
			$(CC) $(FLAGS) -o $@ -c $< $(INCLUDES)

.PHONY	:	all clean fclean re
