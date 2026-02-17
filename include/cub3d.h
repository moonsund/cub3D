#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h> 

typedef struct s_map
{
    char *input_str;

} t_map;

typedef struct s_game
{
    t_map *map;

} t_game;



int main(int argc, char **argv);
void game_loop(t_game *game);
void cleanup_game(t_game *game);
int initialize_game(t_game *game, char *map);











#endif