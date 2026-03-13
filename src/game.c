#include "cub3d.h"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 800

int game_loop(t_game *game)
{
    if (init_graphics(game) != 0)
        return (1);
    if (create_game_window(game) != 0)
        return (1);
    if (init_frame(game) != 0)
        return (1);
    register_hooks(game);
    start_main_loop(game);
    return (0);
}


int init_graphics(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (1);
	return (0);
}

int create_game_window(t_game *game)
{
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (!game->win)
		return (1);


}


void start_main_loop(t_game *game)
{


	mlx_loop(game->mlx);
}