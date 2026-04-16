NAME        = cub3D
BONUS_NAME  = cub3D_bonus
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g

INCLUDES    = -I. -I./minilibx-linux -I./get_next_line

LIBFT       = ./libft/libft.a
MLX         = ./minilibx-linux/libmlx.a
MLX_FLAGS   = -L./minilibx-linux -lmlx -lXext -lX11 -lm -lz

OBJ_DIR     = 	obj

SRC         =	main.c \
				getnextline/get_next_line.c \
				getnextline/get_next_line_utils.c \
				mandatory/init.c \
				mandatory/parsing.c \
				mandatory/raycasting.c

BONUS_SRC   = 	main.c

OBJ         = $(SRC:%.c=$(OBJ_DIR)/%.o)
BONUS_OBJ   = $(BONUS_SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c cub3d.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C ./libft	

$(MLX):
	$(MAKE) -C ./minilibx-linux

bonus: .bonus

.bonus: $(LIBFT) $(MLX) $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFT) $(MLX_FLAGS) -o $(BONUS_NAME)
	@touch .bonus

clean:
	$(MAKE) clean -C ./libft
	$(MAKE) clean -C ./minilibx-linux
	rm -rf $(OBJ_DIR)
	rm -f .bonus 

fclean: clean
	$(MAKE) fclean -C ./libft
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus