NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror

HEADERS = inc/cub3d.h

SRC_DIR = src/

PARSE_DIR = src/parse/

UTILS_DIR = src/utils/

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

GNL_DIR = get_next_line/
GNL = $(GNL_DIR)get_next_line.a

SRCS =	$(SRC_DIR)/main.c \
		$(UTILS_DIR)/utils.c \
		$(UTILS_DIR)/utils2.c \
		$(PARSE_DIR)/collect_map.c \
		$(PARSE_DIR)/flood_fill.c \
		$(PARSE_DIR)/map_parse.c \
		$(PARSE_DIR)/tex_color_parse.c \
		$(PARSE_DIR)/validate_chars.c \

OBJS = $(SRCS:.c=.o)

%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(LIBFT) :
	make -C $(LIBFT_DIR)
	make bonus -C $(LIBFT_DIR)

$(GNL) :
	make -C $(GNL_DIR)

$(NAME) : $(LIBFT) $(GNL) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(GNL)

clean :
	rm -rf $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(GNL_DIR) clean

fclean : clean
	rm -rf $(NAME)
	rm -rf $(OBJS)
	rm -rf $(LIBFT_DIR)libft.a
	rm -rf $(GNL_DIR)get_next_line.a

re: fclean all