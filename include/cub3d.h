#ifndef CUB3D_H
# define CUB3D_H

#include "libft.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_map
{
    t_list *map_data;
    int lines_count;

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
int parse_file(const char *file_path, t_map *map);

// init.c
int initialize_game(t_game *game, char *map);


// game.c
void game_loop(t_game *game);


// utils.c
int print_error(char *error_message);
void cleanup_game(t_game *game);



#endif