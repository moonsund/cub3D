#include "cub3d.h"

void initialize_game(t_game *game)
{
    ft_bzero(&game, sizeof(t_game));
    game->map.floor_color = -1;
    game->map.ceiling_color = -1;
    game->player.pl_x = -1;
    game->player.pl_y = -1;
    game->player.pl_dir = ' ';



}