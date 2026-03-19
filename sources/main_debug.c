#include "cub3d.h"

int main(int argc, char **argv)
{
    t_game game;

    initialize_game(&game);

    if (validate_arguments(argc, argv) == FAILURE)
        return (EXIT_FAILURE);

    if (parse_game_config(argv[1], &game.map, &game.player) == FAILURE)
        return (cleanup_map(&game.map), EXIT_FAILURE);

    debug_dump_parsed(&game);
    
    // Clean up resources
    cleanup_map(&game.map);
    return (0);
}