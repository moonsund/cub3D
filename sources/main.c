#include "cub3d.h"

int main(int argc, char **argv)
{
    t_game game;

    initialize_game(&game);

    if (validate_arguments(argc, argv) == FAILURE)
        return (EXIT_FAILURE);

    if (parse_game_config(argv[1], &game.map, &game.player) == FAILURE)
        return (cleanup_game(&game), EXIT_FAILURE);

    if (game_loop(&game) == FAILURE)
        return (cleanup_game(&game), EXIT_FAILURE);
    
    // Clean up resources
    cleanup_game(&game);
    return (0);
}