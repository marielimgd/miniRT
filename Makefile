# Project Name
NAME        = minirt

# Compiler and Flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -O3 -Ofast -pthread
INCLUDES    = -I$(INC_DIR) -I$(LIBFT_DIR)
LDFLAGS     = -L$(LIBFT_DIR) -lft \
              -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -pthread

# Directories
SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = inc
LIBFT_DIR   = libft
MLX_DIR     = minilibx-linux

# Source Files
SRCS 		= $(shell find $(SRC_DIR) -name "*.c")
OBJS        = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Default target
all: $(NAME)

# Link the final executable
$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)
	@echo "miniRT compiled successfully!"

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean object files
clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "Object files cleaned."

# Remove objects and the final executable
fclean: clean
	@rm -f $(NAME) render.bmp
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "Full clean complete."

# Rebuild everything from scratch
re: fclean all

# Run valgrind with MLX suppression
valgrind: $(NAME)
	@echo "Running valgrind with MLX suppression..."
	@valgrind --leak-check=full \
			  --show-leak-kinds=all \
			  --track-origins=yes \
			  --suppressions=valgrind.supp \
			  --log-file=valgrind-out.txt \
			  ./$(NAME) $(SCENE)
	@echo "Valgrind output saved to valgrind-out.txt"
	@echo "Usage: make valgrind SCENE=scenes/your_scene.rt"

# Quick valgrind check (exits immediately, good for leak checking)
valgrind-quick: $(NAME)
	@echo "Running quick valgrind check..."
	@timeout 2s valgrind --leak-check=full \
						 --show-leak-kinds=definite,indirect \
						 --suppressions=valgrind.supp \
						 ./$(NAME) $(SCENE) || true
	@echo "Quick check complete. For full report use: make valgrind SCENE=..."

norminette:
	@echo "Running norminette on $(LIBFT_DIR) and $(SRC_DIR)..."
	@norminette $(LIBFT_DIR) $(SRC_DIR)

# Phony targets are rules that don't represent actual files
.PHONY: all clean fclean re valgrind valgrind-quick
