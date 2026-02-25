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
    printf("OK\n");

    // Clean up map
    free_map(&map);
    
    return (0);
}