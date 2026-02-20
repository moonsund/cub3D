#ifndef CUB3D_H
# define CUB3D_H

#include "libft.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>


typedef struct s_map
{
    char **file_data;
    size_t lines_count;

    char *tex_N;
    char *tex_S;
    char *tex_E;
    char *tex_W;
    int floor_color;
    int ceiling_color;




} t_map;

typedef struct s_game
{
    t_map *map;

} t_game;



int main(int argc, char **argv);

// validation.c
int validate_arguments(int argc, char **argv);


// parse.c
int initialize_map(const char *file_path, t_map *map);

// parse_helpers.c
int count_lines_in_file(const char *file_path, size_t *lines_count);
void free_file_data(char **file_data, int i);
char *trim_if_needed(char *str);

// init.c
int initialize_game(t_game *game, char *map);


// game.c
void game_loop(t_game *game);


// utils.c
int print_error(char *error_message);
void cleanup_game(t_game *game);
void free_map(t_map *map);


#endif