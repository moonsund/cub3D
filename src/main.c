#include "cub3d.h"

int main(int argc, char **argv)
{
    t_game game;

    initialize_game(&game);

    if (validate_arguments(argc, argv) != 0)
        return (EXIT_FAILURE);

    if (fill_map(argv[1], &game.map) != 0)
        return (cleanup_game(&game), EXIT_FAILURE);

    if (game_loop(&game) != 0)
        return (cleanup_game(&game), EXIT_FAILURE);
    
    // Clean up resources
    cleanup_game(&game);
    return (0);
}