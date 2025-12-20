NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror

HEADERS = src/cub3d.h

SRC_DIR = src/

PARSE_DIR = src/parse/

UTILS_DIR = src/utils/

RENDER_DIR = src/render/

HELPER_DIR = helper_function/

LIBFT_DIR = $(HELPER_DIR)libft/
LIBFT = $(LIBFT_DIR)libft.a

GNL_DIR = $(HELPER_DIR)get_next_line/
GNL = $(GNL_DIR)get_next_line.a

MLX_DIR = $(HELPER_DIR)minilibx-linux/
MLX = $(MLX_DIR)libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

OBJ_DIR = objects/

SRCS =	$(SRC_DIR)/main.c \
        $(UTILS_DIR)/utils.c \
        $(UTILS_DIR)/utils2.c \
        $(PARSE_DIR)/collect_map.c \
        $(PARSE_DIR)/flood_fill.c \
        $(PARSE_DIR)/map_parse.c \
        $(PARSE_DIR)/tex_color_parse.c \
        $(PARSE_DIR)/validate_chars.c \
        $(RENDER_DIR)check_struct.c \
        $(RENDER_DIR)mlx_init.c \
        $(RENDER_DIR)ray_cast.c \
        $(RENDER_DIR)key_hooks.c \
        $(RENDER_DIR)game_loop.c \
		$(RENDER_DIR)rotate_camera.c \
		$(RENDER_DIR)move_player.c \

OBJS = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(LIBFT) :
	make -C $(LIBFT_DIR)
	make bonus -C $(LIBFT_DIR)

$(GNL) :
	make -C $(GNL_DIR)

$(MLX) :
	make -C $(MLX_DIR)

$(NAME) : $(LIBFT) $(GNL) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(GNL) $(MLX_FLAGS)

clean :
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(GNL_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean : clean
	rm -rf $(NAME)
	rm -rf $(LIBFT_DIR)libft.a
	rm -rf $(GNL_DIR)get_next_line.a

re: fclean all