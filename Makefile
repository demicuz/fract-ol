NAME		= fract-ol

# TODO
CC			= clang
CFLAGS		= -g -Wall -O3#-Werror -Wextra

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

MLX_DIR		= minilibx-linux
MLX			= $(MLX_DIR)/libmlx.a

SRC			= main.c mlx_utils.c
OBJ			= $(SRC:.c=.o)
# H			= $(SRC:.c=.h)

# To include only the functions we need, not the whole libft.a
# LIBFT_OBJ	= ft_putchar.o ft_strlen.o ft_strchr.o

.PHONY:	all clean fclean re

all : $(NAME)

# $(LIBFT):
# 	$(MAKE) --directory=$(LIBFT_DIR)

# The reason not to make libft.a build a separate rule is that if some file in
# libft is changed, the rebuild of $(NAME) won't rebuild $(LIBFT) as it doesn't
# Look at .c files, only at libft.a. The other option is to make $(LIBFT) phony
# and for $(NAME) to depend on $(LIBFT), but then we'll have to repackage
# $(NAME) every make, even if nothing has changed. Not good either.

#TODO @$(MAKE) --directory=$(LIBFT_DIR) --silent

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -L . -l:$(LIBFT) -l:$(MLX) -lXext -lX11 -lm -lz -o $(NAME)

# runner: $(OBJ) main.o
# 	@$(CC) $(CFLAGS) $(OBJ) main.o -L . -l:$(LIBFT) -o runner

%.o : %.c #$(H)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(LIBFT_DIR) -I $(MLX_DIR) -I .

clean:
	rm -rf *.o
	$(MAKE) clean --directory=$(LIBFT_DIR)

fclean: clean
	rm -rf $(NAME)
	$(MAKE) fclean --directory=$(LIBFT_DIR)

re: fclean all
