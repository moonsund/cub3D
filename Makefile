NAME = cubed

CC = cc
CFLAGS = -g

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

MLX_DIR = minilibx
MLX_A = $(MLX_DIR)/libmlx.a

HEADER = fdf.h

INCLUDES = -I. -I$(LIBFT_DIR) -I$(MLX_DIR)
LIBS = -Llibft -lft -Lminilibx -lmlx -lX11 -lXext -lm

SRCS = main.c parse.c init_window.c init_window2.c draw.c draw2.c events.c view_controls.c utils.c
OBJS = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A) $(MLX_A) $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_A):
	$(MAKE) -C $(MLX_DIR)


clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all