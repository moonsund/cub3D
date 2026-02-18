#include "cub3d.h"

int main(int argc, char **argv)
{
    t_game game;

    if (validate_input(argc, argv))
    {
        return (EXIT_FAILURE);
    }


    if (argc != 2)
    {
        printf("Usage: %s <map_file>\n", argv[0]);
        return (1);
    }

    // Initialize game state and load the map
    if (!initialize_game(&game, argv[1]))
    {
        printf("Failed to initialize the game.\n");
        return (1);
    }

    // Start the game loop
    game_loop(&game);

    // Clean up resources
    cleanup_game(&game);
    
    return (0);
}