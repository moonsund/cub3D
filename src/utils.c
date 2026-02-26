#include "cub3d.h"

static void print_error_marker(void);
void free_map(t_map *map);

int error_errno(const char *context)
{
    print_error_marker();
    perror(context);
    return (1);
}

int error_exit_msg(const char *error_message)
{
    print_error_marker();
    if (error_message)
        write(2, error_message, ft_strlen(error_message));
    return (1);
}

void cleanup_game(t_game *game)
{
    free_map(game->map);
}

void free_map(t_map *map)
{
    size_t i;

    i = 0;
    while (i < map->lines_count)
        free(map->file_data[i]);
    free(map->file_data);
    free(map->tex_N);
    free(map->tex_E);
    free(map->tex_S);
    free(map->tex_W);
    map->ceiling_color = -1;
    map->floor_color = -1;
    map->grid = NULL;
    map->map_height = 0;
    map->map_width = 0;
    map->player_dir = ' ';
    map->player_x = -1;
    map->player_y = -1;
}

static void print_error_marker(void)
{
    write(2, "Error\n", 6);
}