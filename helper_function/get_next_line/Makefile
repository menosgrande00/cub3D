NAME = get_next_line.a

SRCS =  get_next_line.c \
		get_next_line_utils.c

FLAGS = -c -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	cc $(FLAGS) $(SRCS)
	ar -rc $(NAME) $(OBJS)

all : $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re