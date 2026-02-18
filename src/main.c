#include "cub3d.h"

int main(int argc, char **argv)
{
    t_game game;
    t_map map;

    if (validate_arguments(argc, argv))
        return (EXIT_FAILURE);


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