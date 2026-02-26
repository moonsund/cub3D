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

    debug_dump_parsed(&map);
    
    // Clean up resources
    void cleanup_game(t_game *game);
    printf("OK\n");
    return (0);
}