NAME        = cub3D
BONUS_NAME  = cub3D_bonus
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g

INCLUDES    = -I. -I./minilibx-linux -I./get_next_line

LIBFT       = ./libft/libft.a
MLX         = ./minilibx-linux/libmlx.a
MLX_FLAGS   = -L./minilibx-linux -lmlx -lXext -lX11 -lm -lz -lpthread -ldl

OBJ_DIR     = obj

SRC         =   main.c \
                getnextline/get_next_line.c \
                getnextline/get_next_line_utils.c \
                mandatory/init.c \
                mandatory/parsing.c \
                mandatory/utils/utils.c \
                mandatory/raycasting.c \
                mandatory/init_sprite.c \
                mandatory/valid_map.c \
                mandatory/clean_exit.c \
                mandatory/init_mlx.c \
                mandatory/raycast_draw.c \
                mandatory/utils/parsing_utils/data_handling_utils.c \
                mandatory/utils/parsing_utils/mapper_utils.c \
                mandatory/utils/parsing_utils/mini_utils.c \
                mandatory/mouvement.c

BONUS_SRC   =   main_bonus.c \
                getnextline/get_next_line.c \
                getnextline/get_next_line_utils.c \
                bonus/init_bonus.c \
                bonus/parsing_bonus.c \
                bonus/utils/utils_bonus.c \
                bonus/minimap_bonus.c \
                bonus/raycasting_bonus.c \
                bonus/init_sprite_bonus.c \
                bonus/valid_map_bonus.c \
                bonus/clean_exit_bonus.c \
                bonus/mouse_hook_bonus.c \
                bonus/sprite_bonus.c \
                bonus/torch_bonus.c \
                bonus/BFS_bonus.c \
                bonus/audio_bonus.c \
                bonus/doors_bonus.c \
                bonus/init_mlx_bonus.c \
                bonus/update_sprite_bonus.c \
                bonus/utils/mlx_utils_bonus.c \
                bonus/raycast_draw_bonus.c \
                bonus/utils/parsing_utils/data_handling_utils_bonus.c \
                bonus/utils/parsing_utils/mapper_utils_bonus.c \
                bonus/utils/parsing_utils/mini_utils_bonus.c \
                bonus/mouvement_bonus.c

OBJ         = $(SRC:%.c=$(OBJ_DIR)/%.o)
BONUS_OBJ   = $(BONUS_SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ): cub3d.h
$(BONUS_OBJ): cub3d_bonus.h

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