#ifndef CUB3D_H
#define CUB3D_H

# include "../libs/libft/libft.h"
# include "../libs/minilibx-linux/mlx.h"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>

/* MACROS */
# define SUCCESS 0
# define FAILURE 1

typedef struct s_map
{
    int lines_count;
    char	**file_data;

    char	*tex_N;
    char	*tex_S;
    char	*tex_E;
    char	*tex_W;
    int		floor_color;
    int		ceiling_color;

    char** grid;
    int map_height;
    int map_width;


} t_map;

typedef struct s_player
{
    double  pl_x;
    double  pl_y;
    char    pl_dir;
} t_player;


typedef struct s_game
{
    t_map map;
    t_player player;

    void		*mlx;
	void		*win;

} t_game;

int 	main(int argc, char** argv);

// intit.c
void initialize_game(t_game *game);

// validation.c
int 	validate_arguments(int argc, char** argv);

// PARSING
// parse.c
int parse_game_config(const char *file_path, t_map *map, t_player *player);

// file_loader.c
int count_lines_in_file(const char *file_path, int *lines_count);
int read_file(const char *file_path, t_map *map);
char *trim_if_needed(char *str);
void free_file_data(char **file_data, int i); //TO_DO

// parse_data.c
int process_data_read(t_map *map, t_player *player);
int parse_texture_line(t_map *map, char *str);
int parse_colour_line(t_map *map, char *str);
bool is_texture_identifier(char *str);
bool is_color_identifier(char *str);

// parse_texture_colour_utils.c
int set_texture(char **dst, char *str);
int validate_texture_arg(char *path);
int set_colour(const char *str, int *dst);
int validate_colour_args(char **arr);
void free_split(char **arr);

// parse_map.c
int parse_map_section(t_map *map, t_player *player, int start);
int	build_map_grid(t_map *map, int i);
int find_player_position(t_player *player, char **grid);
int	validate_map_closure(t_map *map, t_player *player);
int	flood_fill(t_map *map, char **grid, int x, int y);

// parse_map_utils.c
void skip_empty_lines(char **lines, int *i);
bool line_is_empty(char *line);
void get_map_dimensions(char **lines, int *height, int *width, int i);
int check_trailing_content(char **lines, int i);
int	validate_map_chars(char **lines, int i);

// parse_map_copy.c
char *copy_line(char *src, size_t width);
char **copy_grid(t_map *map);
void	set_player_position(t_player *player, char dir, int y, int x);






// init.c
void initialize_game(t_game* game);


// game.c
int game_loop(t_game *game);

// utils.c
int error_errno(const char* context);
int error_msg(const char* error_message);
void cleanup_game(t_game* game);
void	free_grid(char **grid);
void print_error_marker(void);
void cleanup_map(t_map *map);

// events.c
void	register_hooks(t_game *game);

// debugging_helpers.c
void print_file_data(t_map* map);
void debug_dump_parsed(const t_game* game);
void print_map_grid(const char** grid, size_t h, size_t w);

#endif