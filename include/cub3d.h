/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asharafe <asharafe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 15:52:41 by asharafe          #+#    #+#             */
/*   Updated: 2026/04/04 22:49:51 by asharafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/libft/libft.h"
# include "../libs/minilibx-linux/mlx.h"
# include <math.h>

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>

/* MACROS */
# define SUCCESS 0
# define FAILURE 1

/* MACROS */
# define WIN_WIDTH 1280
# define WIN_HEIGHT 800

/* MINIMAP */
# define MINIMAP_TILE 12
# define MINIMAP_OFFSET_X 20
# define MINIMAP_OFFSET_Y 20
# define PLAYER_SIZE 4
# define DIR_LINE_LEN 12
# define WALL_COLOUR  0x000000  // black
# define FIELD_COLOUR 0x888888  // light-gray
# define VOID_COLOUR  0x333333  // dark-gray

# ifdef __linux__
#  define ESC_KEY 65307
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define LEFT_ARROW 65361
#  define RIGHT_ARROW 65363
# else
#  define ESC_KEY 53
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define LEFT_ARROW 123
#  define RIGHT_ARROW 124
# endif

typedef struct s_ray
{
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	int				step_x;
	int				step_y;
	int				side;
	double			perp_wall_dist;
	int				line_height;
	int				draw_start;
	int				draw_end;
}	t_ray;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
}	t_img;

typedef struct s_tex
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	int				width;
	int				height;
	unsigned int	*pixels;
}	t_tex;

typedef struct s_map
{
	int				lines_count;
	char			**file_data;
	char			*tex_n;
	char			*tex_s;
	char			*tex_e;
	char			*tex_w;
	int				floor_color;
	int				ceiling_color;
	char			**grid;
	int				map_height;
	int				map_width;
}	t_map;

typedef struct s_player
{
	double			pl_x;
	double			pl_y;
	char			pl_dir;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
}	t_player;

typedef struct s_game
{
	t_map			map;
	t_player		player;
	void			*mlx;
	void			*win;
	t_img			frame;
	t_tex			tex_no;
	t_tex			tex_so;
	t_tex			tex_we;
	t_tex			tex_ea;
	int				key_w;
	int				key_s;
	int				key_a;
	int				key_d;
	int				key_left;
	int				key_right;
}	t_game;

int				main(int argc, char **argv);

// intit.c
void			initialize_game(t_game *game);

// validation.c
int				validate_arguments(int argc, char **argv);

// parse.c
int				parse_game_config(const char *file_path, 
					t_map *map, t_player *player);

// file_loader.c
int				count_lines_in_file(const char *file_path, int *lines_count);
int				read_file(const char *file_path, t_map *map);
char			*trim_if_needed(char *str);
void			free_file_data(char **file_data, int i); //TO_DO

// parse_data.c
int				process_data_read(t_map *map, t_player *player);
int				parse_map_params_lines(t_map *map, char *line, int *params);
int				parse_texture_line(t_map *map, char *str);
int				parse_colour_line(t_map *map, char *str);

// parse_texture_colour_utils.c
int				set_texture(char **dst, char *str);
int				validate_texture_arg(char *path);
int				set_colour(const char *str, int *dst);
int				validate_colour_args(char **arr);
void			free_split(char **arr);

// parse_map.c
int				parse_map_section(t_map *map, t_player *player, int start);
int				build_map_grid(t_map *map, int i);
int				find_player_position(t_player *player, char **grid);
int				validate_map_closure(t_map *map, t_player *player);
int				flood_fill(t_map *map, char **grid, int x, int y);

// parse_map_utils.c
void			skip_empty_lines(char **lines, int *i);
bool			line_is_empty(char *line);
void			get_map_dimensions(char **lines, int *height, 
					int *width, int i);
int				check_trailing_content(char **lines, int i);
int				validate_map_chars(char **lines, int i);
int				ft_map_line_length(char *line);

// parse_map_copy.c
char			*copy_line(char *src, size_t width);
char			**copy_grid(t_map *map);
void			set_player_position(t_player *player, char dir, int y, int x);

// game_loop.c
int				game_loop(t_game *game);
// void	start_main_loop(t_game *game);

// init_graphics.c
int				init_graphics(t_game *game);
int				create_game_window(t_game *game);
int				init_frame(t_game *game);

// render.c
void			put_pixel(t_img *img, int x, int y, int color);
void			draw_background(t_game *game);
void			render_frame(t_game *game);
int				game_render_loop(t_game *game);
bool			is_wall(t_game *game, int x, int y);

// events.c
int				close_game(t_game *game);
int				key_press(int keycode, t_game *game);
void			register_hooks(t_game *game);
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
void			register_hooks(t_game *game);

// player_init.c
void			init_player_direction(t_player *player);

// movement.c
void			update_player(t_game *game);
void			rotate_left(t_game *game, double rot_speed);
void			rotate_right(t_game *game, double rot_speed);

// movement_utils.c
void			move_forward(t_game *game, double move_speed);
void			move_backward(t_game *game, double move_speed);
void			move_left(t_game *game, double move_speed);
void			move_right(t_game *game, double move_speed);

// raycast.c
void			raycast(t_game *game);

// textures.c
int				load_textures(t_game *game);
int				load_texture_image(void *mlx, char *path, t_tex *tex);
unsigned int	get_texture_pixel(t_tex *tex, int x, int y);

// texture_render.c
void			draw_textured_wall(t_game *game, int x, t_ray *ray);

// minimap.c
void			draw_minimap(t_game *game);

// utils.c
int				error_errno(const char *context);
int				error_msg(const char *error_message);
void			cleanup_game(t_game *game);
void			free_grid(char **grid);
void			print_error_marker(void);
void			cleanup_map(t_map *map);

// debugging_helpers.c
void			print_file_data(t_map *map);
void			debug_dump_parsed(const t_game *game);
void			print_map_grid(const char **grid, size_t h, size_t w);

#endif