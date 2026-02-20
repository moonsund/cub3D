NAME        := cub3d
DEBUG_NAME  := cub3d_debug

SRC_DIR     := src
OBJ_DIR     := obj
DBG_OBJ_DIR := obj_debug
INC_DIR     := include
LIBS_DIR    := libs

LIBFT_DIR   := $(LIBS_DIR)/libft
MLX_DIR     := $(LIBS_DIR)/minilibx-linux

LIBFT_A     := $(LIBFT_DIR)/libft.a
MLX_A       := $(MLX_DIR)/libmlx.a

CC          := cc
RM          := rm -f
RMR         := rm -rf
MKDIR_P     := mkdir -p

CPPFLAGS    := -I$(INC_DIR) -I$(LIBFT_DIR)

CFLAGS      := -Wall -Wextra -Werror
DBG_CFLAGS  := -g -Wall -Wextra -Werror -Iinclude

# Full build link flags (linux mlx)
LDFLAGS     := -L$(LIBFT_DIR) -L$(MLX_DIR)
LDLIBS      := -lft -lmlx -lXext -lX11 -lm -lz

# Debug build link flags (NO MLX)
DBG_LDFLAGS := -L$(LIBFT_DIR)
DBG_LDLIBS  := -lft

# =======================
# Sources
# =======================
SRCS := \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/validation.c \
	$(SRC_DIR)/init.c \
	$(SRC_DIR)/parse.c \
	$(SRC_DIR)/parse_helpers.c \
	$(SRC_DIR)/events.c \
	$(SRC_DIR)/game.c \
	$(SRC_DIR)/utils.c

# ВАЖНО: никаких файлов, которые используют mlx_*
DEBUG_SRCS := \
	$(SRC_DIR)/main_debug.c \
	$(SRC_DIR)/validation.c \
	$(SRC_DIR)/init.c \
	$(SRC_DIR)/parse.c \
	$(SRC_DIR)/parse_helpers.c \
	$(SRC_DIR)/utils.c

OBJS       := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS       := $(OBJS:.o=.d)

DEBUG_OBJS := $(DEBUG_SRCS:$(SRC_DIR)/%.c=$(DBG_OBJ_DIR)/%.o)
DEBUG_DEPS := $(DEBUG_OBJS:.o=.d)

.PHONY: all debug bootstrap deps deps_libft deps_full depscheck depscheck_libft \
        clean fclean re distclean

# =======================
# Main targets
# =======================
all: depscheck_full $(NAME)
debug: depscheck_libft $(DEBUG_NAME)

bootstrap: deps_full all

# =======================
# Link
# =======================
$(NAME): $(OBJS) $(LIBFT_A) $(MLX_A)
	$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@

$(DEBUG_NAME): $(DEBUG_OBJS) $(LIBFT_A)
	$(CC) $(DEBUG_OBJS) $(DBG_LDFLAGS) $(DBG_LDLIBS) -o $@

# =======================
# Compile + auto deps
# =======================
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MP -c $< -o $@

$(DBG_OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(DBG_CFLAGS) $(CPPFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS)
-include $(DEBUG_DEPS)

# =======================
# deps: submodules
# =======================
deps_libft:
	@$(MKDIR_P) $(LIBS_DIR)
	@echo ">> Updating libft submodule"
	@git submodule update --init --recursive $(LIBFT_DIR)

deps_full:
	@$(MKDIR_P) $(LIBS_DIR)
	@echo ">> Updating all submodules"
	@git submodule update --init --recursive

# =======================
# depscheck (split!)
# =======================
depscheck_libft:
	@$(MKDIR_P) $(LIBS_DIR)
	@if [ ! -f ".gitmodules" ]; then \
		echo "Missing .gitmodules (submodules not configured)."; exit 1; \
	fi
	@if [ ! -f "$(LIBFT_DIR)/Makefile" ]; then \
		echo "libft is not initialized."; \
		echo "Run: make deps_libft"; \
		exit 1; \
	fi

depscheck_full:
	@$(MKDIR_P) $(LIBS_DIR)
	@if [ ! -f ".gitmodules" ]; then \
		echo "Missing .gitmodules (submodules not configured)."; exit 1; \
	fi
	@if [ ! -f "$(LIBFT_DIR)/Makefile" ] || [ ! -f "$(MLX_DIR)/Makefile" ]; then \
		echo "Dependencies are not initialized."; \
		echo "Run: make deps_full"; \
		exit 1; \
	fi

# =======================
# Build libs
# =======================
$(LIBFT_A): depscheck_libft
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_A): depscheck_full
	@if [ ! -f "$(MLX_DIR)/Makefile.gen" ]; then \
		echo ">> Configuring minilibx-linux"; \
		cd $(MLX_DIR) && ./configure; \
	fi
	$(MAKE) -C $(MLX_DIR)

# =======================
# Cleaning
# =======================
clean:
	$(RMR) $(OBJ_DIR) $(DBG_OBJ_DIR)
	@if [ -f "$(LIBFT_DIR)/Makefile" ]; then \
		$(MAKE) -C $(LIBFT_DIR) clean; \
	fi
	@if [ -f "$(MLX_DIR)/Makefile" ]; then \
		$(MAKE) -C $(MLX_DIR) clean; \
	fi

fclean: clean
	$(RM) $(NAME) $(DEBUG_NAME)

re: fclean all

distclean: fclean
	@echo ">> Deinitializing submodules (keeping $(LIBS_DIR)/)"
	@git submodule deinit -f --all || true
	@$(RMR) $(LIBFT_DIR) $(MLX_DIR)
	@$(MKDIR_P) $(LIBS_DIR)
