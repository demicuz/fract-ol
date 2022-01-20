NAME		:= fract-ol

SRC_DIR		:= src
OBJ_DIR		:= obj
LIB_DIR		:= lib

LIBFT_DIR	:= libft
MLX_DIR		:= minilibx-linux

LIBFT		:= $(LIB_DIR)/libft.a
LIBMLX		:= $(LIB_DIR)/libmlx.a

SRC_FILES	:= complex.c float_parser.c graphics_utils.c julia.c keyboard.c \
               main.c mandelbrot.c mouse.c ship.c
SRC			:= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ			:= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# TODO
CC			:= clang
CPPFLAGS	:= -I include -I $(LIBFT_DIR) -I $(MLX_DIR) -MMD -MP
CFLAGS		:= -g -O3#-Wall -Werror -Wextra
LDFLAGS		:= -L$(LIB_DIR)
LDLIBS		:= -lft -lmlx -lXext -lX11 -lm -lz

.PHONY:	all bonus clean fclean re

all: $(NAME)

bonus: $(NAME)

$(LIBFT): $(LIB_DIR)
	$(MAKE) --directory=$(LIBFT_DIR)
	cp $(LIBFT_DIR)/libft.a $(LIB_DIR)

$(LIBMLX): $(LIB_DIR)
	$(MAKE) --directory=$(MLX_DIR)
	cp $(MLX_DIR)/libmlx.a $(LIB_DIR)

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

-include $(OBJ:.o=.d)
