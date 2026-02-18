NAME        := cub3d

SRC_DIR     := src
OBJ_DIR     := obj
INC_DIR     := include
LIBS_DIR    := libs

LIBFT_DIR   := $(LIBS_DIR)/libft
MLX_DIR     := $(LIBS_DIR)/minilibx-linux

LIBFT_A     := $(LIBFT_DIR)/libft.a
MLX_A       := $(MLX_DIR)/libmlx.a

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
CFLAGS      := -Wall -Wextra -Werror
CPPFLAGS    := -I$(INC_DIR)

LDFLAGS     := -L$(LIBFT_DIR) -L$(MLX_DIR)
LDLIBS      := -lft -lmlx -lXext -lX11 -lm -lz

RM          := rm -f
RMR         := rm -rf
MKDIR_P     := mkdir -p

.PHONY: all bootstrap deps depscheck clean fclean re distclean


# Main targets
all: depscheck $(NAME)

bootstrap: deps all

$(NAME): $(OBJS) $(LIBFT_A) $(MLX_A)
	$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@


# Objects (+ auto deps .d)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS)


# Submodules init/update
deps:
	@$(MKDIR_P) $(LIBS_DIR)
	@echo ">> Updating git submodules"
	@git submodule update --init --recursive

depscheck:
	@# libs/ should exist even before deps
	@$(MKDIR_P) $(LIBS_DIR)
	@if [ ! -f ".gitmodules" ]; then \
		echo "Missing .gitmodules (submodules not configured)."; \
		exit 1; \
	fi
	@if [ ! -f "$(LIBFT_DIR)/Makefile" ] || [ ! -f "$(MLX_DIR)/Makefile" ]; then \
		echo "Dependencies (submodules) are not initialized."; \
		echo "Run: make deps"; \
		exit 1; \
	fi


# libft
$(LIBFT_A): depscheck
	$(MAKE) -C $(LIBFT_DIR)

# minilibx-linux
$(MLX_A): depscheck
	@if [ ! -f "$(MLX_DIR)/Makefile.gen" ]; then \
		echo ">> Configuring minilibx-linux"; \
		cd $(MLX_DIR) && ./configure; \
	fi
	$(MAKE) -C $(MLX_DIR)


# Cleaning
clean:
	$(RMR) $(OBJ_DIR)
	@if [ -f "$(LIBFT_DIR)/Makefile" ]; then \
		$(MAKE) -C $(LIBFT_DIR) clean; \
	fi
	@if [ -f "$(MLX_DIR)/Makefile" ]; then \
		$(MAKE) -C $(MLX_DIR) clean; \
	fi

fclean: clean
	$(RM) $(NAME)

re: fclean all

distclean: fclean
	@echo ">> Deinitializing submodules (keeping $(LIBS_DIR)/)"
	@git submodule deinit -f --all || true
	@# remove checked-out working trees, but keep libs/ directory itself
	@$(RMR) $(LIBFT_DIR) $(MLX_DIR)
	@$(MKDIR_P) $(LIBS_DIR)
