#include "cub3d.h"

int main(int argc, char **argv)
{
    t_map map;
    t_game game;

    (void)game;
    if (validate_arguments(argc, argv))
        return (EXIT_FAILURE);

    if (!initialize_map(argv[1], &map))
        return (EXIT_FAILURE); 

    debug_dump_parsed(&map);
    printf("OK\n");

    // Clean up map
    free_map(&map);
    
    return (0);
}