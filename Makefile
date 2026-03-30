# ===================================================== #
#              cub3d Makefile usage                     #
#  - help info             help                         #
#  - release build:        make / make all              #
#  - debug (no mlx):       make debug                   #
#  - tests (parser):       make test_parser             #
#  - memcheck:             make memcheck                #
#  - memcheck & tests:     make test_parser_memcheck    #
#  - lint (cppcheck):      make lint_cppcheck           #
#  - format:               make format                  #
# ===================================================== #


NAME        := cub3d
DEBUG_NAME  := cub3d_debug

SRC_DIR     := sources
OBJ_DIR     := objects
DBG_OBJ_DIR := obj_debug
INC_DIR     := include
LIBS_DIR    := libs

LIBFT_DIR   := $(LIBS_DIR)/libft
MLX_DIR     := $(LIBS_DIR)/minilibx-linux

LIBFT_A     := $(LIBFT_DIR)/libft.a
MLX_A       := $(MLX_DIR)/libmlx.a

# =======================
# Tools
# =======================
CC          := cc
RM          := rm -f
RMR         := rm -rf
MKDIR_P     := mkdir -p

# =======================
# Flags
# =======================
# C PreProcessor FLAGS
CPPFLAGS    := -I$(INC_DIR) -I$(LIBFT_DIR)
# C FLAGS
CFLAGS      := -Wall -Wextra -Werror
DBG_CFLAGS  := $(CFLAGS) -g

# Full build linker flags (Linux mlx)
# LoaDer FLAGS
LDFLAGS     := -L$(LIBFT_DIR) -L$(MLX_DIR)
# LoaDer LIBrarieS FLAGS
LDLIBS      := -lft -lmlx -lXext -lX11 -lm -lz

# Debug build linker flags (NO MLX)
DBG_LDFLAGS := -L$(LIBFT_DIR)
DBG_LDLIBS  := -lft

# cppcheck flags
CPPCHECK_FLAGS := \
  --language=c \
  --std=c11 \
  --enable=warning,style,performance,portability \
  --inconclusive \
  --inline-suppr \
  --error-exitcode=1 \
  --suppress=missingIncludeSystem

CPPCHECK_EXCLUDE := \
  -i$(MLX_DIR) \
  -i$(LIBFT_DIR) \
  -ibuild -iobj -iobjs

# ==========
# OS detect
# ==========
UNAME_S := $(shell uname -s)

# ==========
# Tests Tools
# ==========
PY          	?= python3
TEST_RUNNER 	?= tests/run_parser_tests.py

VALGRIND    	?= valgrind
LEAKS       	?= leaks
CPPCHECK    	?= cppcheck
CLANG_FORMAT	?= clang-format

# Usage: make memcheck ARGS="maps/map.cub"
ARGS ?=

# Valgrind options (Linux)
VALGRIND_OPTS ?= --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=42

# leaks options (macOS)
LEAKS_ENV  ?= MallocStackLogging=1
LEAKS_OPTS ?= --atExit --

# =======================
# Sources
# =======================

SRC_MAIN = \
	main.c

DEBUG_SRC_MAIN = \
	main_debug.c

DEBUG_SRC_DEBUGGING = \
	debugging/debugging_helpers.c

SRC_PARSING = \
	parsing/parser.c \
	parsing/parse_file.c \
	parsing/parse_data.c \
	parsing/parse_data_utils.c \
	parsing/parse_map.c \
	parsing/parse_map_utils.c \
	parsing/parse_map_copy.c \

SRC_GAME = \
	game/events.c \
	game/game_loop.c \
	game/init_graphics.c \
	game/player_init.c \
	game/render.c \
	game/raycast.c \
	game/raycast_utils.c \
	game/movement.c \
	game/textures.c \
	game/textures_render.c \
	game/minimap.c \

SRC_INIT = \
	init/init.c \
	init/utils.c \
	init/validation.c \
	
SRC_FILES = \
	$(SRC_MAIN) \
	$(SRC_PARSING) \
	$(SRC_GAME) \
	$(SRC_INIT) \

# no files that use mlx_*
DEBUG_SRC_FILES = \
	$(DEBUG_SRC_MAIN) \
	$(SRC_PARSING) \
	$(DEBUG_SRC_DEBUGGING) \
	$(SRC_INIT) \


# $(VAR:pattern=replacement)
SRCS := $(addprefix $(SRC_DIR)/,$(SRC_FILES))
OBJS := $(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))
DEPS       := $(OBJS:.o=.d)

DEBUG_SRCS := $(addprefix $(SRC_DIR)/,$(DEBUG_SRC_FILES))
DEBUG_OBJS := $(addprefix $(DBG_OBJ_DIR)/,$(DEBUG_SRC_FILES:.c=.o))
DEBUG_DEPS := $(DEBUG_OBJS:.o=.d)

.PHONY: all debug bootstrap deps_libft deps_full depscheck \
        depscheck_libft clean fclean re distclean format help

# =======================
# Main targets
# =======================
.DEFAULT_GOAL := all

all: depscheck_full $(NAME)
debug: depscheck_libft $(DEBUG_NAME)

bootstrap: deps_full all

help:
	@echo "Targets:"
	@echo "  all / make            - build release (with MLX on Linux)"
	@echo "  debug                 - build debug binary (no MLX)"
	@echo "  test_parser           - run parser tests (requires debug binary)"
	@echo "  memcheck              - run leak check (auto: Linux=valgrind, macOS=leaks; usage: make memcheck ARGS=./map.cub)"
	@echo "  test_parser_memcheck  - run leak check with parser tests"
	@echo "  lint_cppcheck         - static analysis with cppcheck (installation may be required)"
	@echo "  format                - format sources with clang-format (installation may be required)"
	@echo "  clean / fclean / re   - cleanup / full cleanup / rebuild"

# =======================
# Tests
# =======================
test_parser: $(DEBUG_NAME)
	BIN=./$(DEBUG_NAME) $(PY) $(TEST_RUNNER)

# =======================
# Memcheck light (auto per OS)
# =======================
memcheck: $(DEBUG_NAME)
ifeq ($(UNAME_S),Linux)
	$(VALGRIND) $(VALGRIND_OPTS) ./$(DEBUG_NAME) $(ARGS)
else ifeq ($(UNAME_S),Darwin)
	env $(LEAKS_ENV) $(LEAKS) $(LEAKS_OPTS) ./$(DEBUG_NAME) $(ARGS)
else
	@echo "Unsupported OS: $(UNAME_S)"
	@exit 1
endif

# =======================
# Memcheck with maps parsing (auto per OS)
# =======================
test_parser_memcheck: $(DEBUG_NAME)
ifeq ($(UNAME_S),Linux)
	RUN_PREFIX='$(VALGRIND) $(VALGRIND_OPTS)' BIN=./$(DEBUG_NAME) $(PY) $(TEST_RUNNER)
else ifeq ($(UNAME_S),Darwin)
	env RUN_PREFIX='$(LEAKS_ENV) $(LEAKS) $(LEAKS_OPTS)' BIN=./$(DEBUG_NAME) $(PY) $(TEST_RUNNER)
else
	@echo "Unsupported OS: $(UNAME_S)"
	@exit 1
endif

# =======================
# Lint / format (no clang-tidy)
# =======================
lint_cppcheck:
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(CPPCHECK_EXCLUDE) $(CPPFLAGS) $(SRCS)

format:
	$(CLANG_FORMAT) -i $(SRCS) $(DEBUG_SRCS)

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