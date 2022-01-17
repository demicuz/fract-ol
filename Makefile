NAME		:= fract-ol

SRC_DIR		:= src
OBJ_DIR		:= obj
LIB_DIR		:= lib

LIBFT_DIR	:= libft
MLX_DIR		:= minilibx-linux

LIBFT		:= $(LIB_DIR)/libft.a
LIBMLX		:= $(LIB_DIR)/libmlx.a

SRC_FILES	:= main.c mlx_utils.c
SRC			:= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ			:= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# TODO
CC			:= clang
CPPFLAGS	:= -I include -MMD -MP
CFLAGS		:= -g -Wall -O3#-Werror -Wextra
LDFLAGS		:= -L$(LIB_DIR)
LDLIBS		:= -lft -lmlx -lXext -lX11 -lm -lz

.PHONY:	all bonus clean fclean re wat

all: $(NAME)

bonus: $(NAME)

$(LIBFT): $(LIB_DIR)
	$(MAKE) --directory=$(LIBFT_DIR)
	cp $(LIBFT_DIR)/libft.a $(LIB_DIR)

$(LIBMLX): $(LIB_DIR)
	$(MAKE) --directory=$(MLX_DIR)
	cp $(MLX_DIR)/libmlx.a $(LIB_DIR)

# The reason not to make libft.a build a separate rule is that if some file in
# libft is changed, the rebuild of $(NAME) won't rebuild $(LIBFT) as it doesn't
# Look at .c files, only at libft.a. The other option is to make $(LIBFT) phony
# and for $(NAME) to depend on $(LIBFT), but then we'll have to repackage
# $(NAME) every make, even if nothing has changed. Not good either.

$(NAME): $(OBJ) $(LIBFT) $(LIBMLX)
	$(CC) $(LDFLAGS) $(OBJ) $(LDLIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR) $(LIB_DIR):
	mkdir -p $@

clean:
	rm -rv $(OBJ_DIR)
	$(MAKE) clean --directory=$(LIBFT_DIR)
	$(MAKE) clean --directory=$(MLX_DIR)

fclean: clean
	rm $(NAME)
	$(MAKE) fclean --directory=$(LIBFT_DIR)

re: fclean all
