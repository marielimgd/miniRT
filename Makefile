# Project Name
NAME        = miniRT

# Compiler and Flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -O3 -Ofast
INCLUDES    = -I$(INC_DIR) -I$(LIBFT_DIR)
LDFLAGS     = -L$(LIBFT_DIR) -lft \
              -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

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
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "Full clean complete."

# Rebuild everything from scratch
re: fclean all

# Phony targets are rules that don't represent actual files
.PHONY: all clean fclean re
