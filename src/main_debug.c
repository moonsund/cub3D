#include "cub3d.h"

static void print_map(t_map *map);

int main(int argc, char **argv)
{
    t_map map;
    t_game game;

    (void)game;
    if (validate_arguments(argc, argv))
        return (EXIT_FAILURE);

    if (!initialize_map(argv[1], &map))
        return (EXIT_FAILURE); 

    print_map(&map);
    printf("OK\n");

    // Clean up map
    free_map(&map);
    
    return (0);
}

static void print_map(t_map *map) // for debug. to be deleted.
{
    size_t i = 0;
    while (i < map->lines_count)
    {
        printf("#%zu: %s\n", i, map->file_data[i]);
        i++;
    }
}