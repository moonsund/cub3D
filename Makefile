NAME        := cub3d

SRC_DIR     := src
OBJ_DIR     := obj
INC_DIR     := include

SRCS        := \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/init.c \
	$(SRC_DIR)/parse.c \
	$(SRC_DIR)/events.c \
	$(SRC_DIR)/game.c \
	$(SRC_DIR)/utils.c

OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS        := $(OBJS:.o=.d)

CC          := cc
CPPFLAGS    := -I$(INC_DIR)
CFLAGS      := -Wall -Wextra -Werror
LDFLAGS     :=
LDLIBS      :=

LIBS_DIR    := libs
LIBFT_DIR   := $(LIBS_DIR)/libft
MLX_DIR     := $(LIBS_DIR)/minilibx-linux

LIBFT_A     := $(LIBFT_DIR)/libft.a
MLX_A       := $(MLX_DIR)/libmlx.a

LDFLAGS     += -L$(LIBFT_DIR) -L$(MLX_DIR)
LDLIBS      += -lft -lmlx -lXext -lX11 -lm -lz

RM          := rm -f
RMR         := rm -rf
MKDIR_P     := mkdir -p

.PHONY: all bootstrap deps depscheck clean fclean re distclean

all: depscheck $(NAME)

bootstrap: deps all

$(NAME): $(OBJS) $(LIBFT_A) $(MLX_A)
	$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS)

$(LIBFT_A): depscheck
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_A): depscheck
	@if [ ! -f "$(MLX_DIR)/Makefile.gen" ]; then \
		echo ">> Configuring minilibx-linux"; \
		cd $(MLX_DIR) && ./configure; \
	fi
	$(MAKE) -C $(MLX_DIR)

deps:
	@echo ">> Initializing git submodules"
	@git submodule update --init --recursive

depscheck:
	@if [ ! -f "$(LIBFT_DIR)/Makefile" ] || [ ! -f "$(MLX_DIR)/Makefile" ]; then \
		echo "Dependencies missing."; \
		echo "Run: make deps"; \
		exit 1; \
	fi

clean:
	$(RMR) $(OBJ_DIR)
	@if [ -f "$(LIBFT_DIR)/Makefile" ]; then $(MAKE) -C $(LIBFT_DIR) clean; fi
	@if [ -f "$(MLX_DIR)/Makefile" ]; then $(MAKE) -C $(MLX_DIR) clean; fi

fclean: clean
	$(RM) $(NAME)

re: fclean all

distclean: fclean
	@echo ">> Removing dependencies"
	@git submodule deinit -f --all || true
	$(RMR) $(LIBFT_DIR) $(MLX_DIR)
	$(RMR) .git/modules/$(LIBS_DIR)
