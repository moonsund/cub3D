#include "cub3d.h"

int main(int argc, char **argv)
{
    t_map map;
    t_game game;

    (void)game;
    if (validate_arguments(argc, argv) != 0)
        return (EXIT_FAILURE);

    if (fill_map(argv[1], &map) != 0)
        return (EXIT_FAILURE);

    if (!initialize_game(&game, argv[1]))
    {
        printf("Failed to initialize the game.\n");
        return (EXIT_FAILURE);
    }

    game_loop(&game);

    // Clean up resources
    cleanup_game(&game);

    printf("OK\n");
    return (0);
}