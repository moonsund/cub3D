#ifndef CUB3D_H
# define CUB3D_H

#include "libft.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct s_map
{
    char *input_str;

} t_map;

typedef struct s_game
{
    t_map *map;

} t_game;



int main(int argc, char **argv);

// validation.c
int validate_input(int argc, char **argv);


// init.c
int initialize_game(t_game *game, char *map);


// game.c
void game_loop(t_game *game);


// utils.c
int print_error(char *error_message);
void cleanup_game(t_game *game);



#endif