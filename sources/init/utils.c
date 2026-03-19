#include "cub3d.h"

int error_errno(const char *context)
{
    print_error_marker();
    perror(context);
    return (FAILURE);
}

int error_msg(const char *error_message)
{
    print_error_marker();
    if (error_message)
	{
        write(2, error_message, ft_strlen(error_message));
        write(2, "\n", 1);
	}
    return (FAILURE);
}

void print_error_marker(void)
{
    write(2, "Error\n", 6);
}

// void cleanup_game(t_game *game)
// {
//     if (!game)
//         return;
//     cleanup_map(&game->map);
//     if (game->win)
//         mlx_destroy_window(game->mlx, game->win);

//     if (game->mlx)
//     {
//         mlx_destroy_display(game->mlx);
//         free(game->mlx);
//     }
// }

void cleanup_map(t_map *map)
{
    int i;

    if (map->file_data)
    {
        i = 0;
        while (i < map->lines_count)
        {
            free(map->file_data[i]);
            i++;
        }
        map->file_data = NULL;
    }   
    free(map->tex_N);
    map->tex_N = NULL;
    free(map->tex_E);
    map->tex_E = NULL;
    free(map->tex_S);
    map->tex_S = NULL;
    free(map->tex_W);
    map->tex_W = NULL;
    free_grid(map->grid);
	map->grid = NULL;
}

void	free_grid(char **grid)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}